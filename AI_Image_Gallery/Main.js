function CopyToClipboard(text) {
    navigator.clipboard.writeText(text);
}

function CreateKeywordsList(){
    const overlayDiv = document.getElementById('keywordsOverlay');

    document.getElementById('show-all-keywords').addEventListener('click', () => {
        overlayDiv.classList.add('show');
    });
    document.getElementById('closeKeywordsOverlay').addEventListener('click', () => {
        overlayDiv.classList.remove('show');
    });

    const images = document.getElementById('gallery').querySelectorAll('img');

    const keywords = new Map();
    for (const image of images) {
        const imageKeywords = image.dataset.keywords.toLowerCase().split(',');
        for (const imageKeyword of imageKeywords) {
            const trimmedKeyword = imageKeyword.trim();
            const count = keywords.get(trimmedKeyword) || 0;
            keywords.set(trimmedKeyword, count + 1);
        }
    }

    const sortedKeywords = Array.from(keywords.entries()).sort((a, b) => b[1] - a[1]);

    const keywordList = overlayDiv.querySelector('ul');
    keywordList.innerHTML = '';

    for (const [keyword, count] of sortedKeywords) {
        const listItem = document.createElement('li');

        const button = document.createElement('button');
        button.textContent = 'Copy';
        button.addEventListener('click', () => CopyToClipboard(keyword));

        listItem.appendChild(button);
        listItem.appendChild(document.createTextNode(` ${keyword} (${count})`));
        
        keywordList.appendChild(listItem);
    }
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function readFile(file) {
    const result = await new Promise((resolve) => {
        const reader = new FileReader();
        reader.onload = () => resolve(reader.result);
        reader.readAsText(file);
    });
    return result;
}

function extractKeywords(firstLine) {
    const regex = /(?<!\\)\((?:(?<!\\)\((?:\\[\s\S]|[^()]*)*\)|\\[\s\S]|[^()])*(?<!\\)\)/g;
    const keywords = firstLine.replace(regex, '').match(/[^,\n]+/g);
    return keywords;
}

function createImageOverlay(prompt, negativePrompt, generationParams) {
    const overlay = document.createElement('div');
    overlay.classList.add('overlay');

    const promptButton = document.createElement('button');
    promptButton.innerText = 'Copy prompt';
    promptButton.addEventListener('click', () => CopyToClipboard(prompt));
    overlay.appendChild(promptButton);

    const negativePromptButton = document.createElement('button');
    negativePromptButton.innerText = 'Copy negative prompt';
    negativePromptButton.addEventListener('click', () => CopyToClipboard(negativePrompt));
    overlay.appendChild(negativePromptButton);

    const generationParamsText = document.createElement('p');
    generationParamsText.innerText = generationParams;
    overlay.appendChild(generationParamsText);

    const closeButton = document.createElement('button');
    closeButton.innerText = 'Close';
    closeButton.addEventListener('click', () => {
        overlay.remove();
    });
    overlay.appendChild(closeButton);
    return overlay;
}


const galleryDiv = document.getElementById('gallery');

async function addImage(path, keywords, textFile) {
    const image = document.createElement('img');
    image.src = path;
    image.classList.add('image');
    image.dataset.keywords = keywords.join(',');
    image.title = keywords.join(',');
    galleryDiv.append(image);

    image.addEventListener('click', async () => {
        const text = (await readFile(textFile)).split('\n');
        const prompt = text[0];
        const negativePrompt = text[1].replace('Negative prompt: ','');
        const generationParams = text[2];

        const overlay = createImageOverlay(prompt, negativePrompt, generationParams);
        document.body.appendChild(overlay);
    });
}

const filterInput = document.getElementById('filterInput');
filterInput.addEventListener('input', () => {
    const filter = filterInput.value.toLowerCase();
    const images = galleryDiv.querySelectorAll('img');
    if (filter === '') {
        for (const image of images) {
            image.classList.remove('hidden');
        }
        return;
    }
    const keywords = filter.split(',');
    for (const image of images) {
        const imageKeywords = image.dataset.keywords.toLowerCase().split(',');
        const matches = keywords.every(keyword =>
            imageKeywords.some(imageKeyword => imageKeyword.trim() === keyword.trim())
        );
        if (matches) {
            image.classList.remove('hidden');
        } else {
            image.classList.add('hidden');
        }
    }
});

const loadFolderButton = document.getElementById('loadFolder');

loadFolderButton.addEventListener('click', async () => {
    const folderInput = document.getElementById('folder-input');
    var startTime = performance.now();
    let imgcount = 0;
    const filecount = folderInput.files.length;
    const promises = Array.from(folderInput.files)
    .filter((file) => file.name.match(/\.txt$/))
    .sort((a,b) => parseInt(b.name.substring(0,5)) - parseInt(a.name.substring(0,5)))
    .map(async file => {
        const text = await readFile(file);
        const firstLine = text.split('\n')[0];

        const keywords = extractKeywords(firstLine);
        const pngFilePath = './' + file.webkitRelativePath.replace('.txt', '.png');
        imgcount++;
        addImage(pngFilePath, keywords, file);
        return sleep(1);
    });
    await Promise.all(promises);

    loadFolderButton.classList.add('hidden');
    folderInput.classList.add('hidden');

    CreateKeywordsList();

    var endTime = performance.now();
    alert(`Finished loading ${imgcount} images (${filecount} files) in ${endTime - startTime} ms`);
}, {once: true});