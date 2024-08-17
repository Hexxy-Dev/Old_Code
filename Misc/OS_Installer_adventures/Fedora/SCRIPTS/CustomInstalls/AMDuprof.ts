import { chromium, Browser, Page } from 'playwright';

(async () => {
    const browser: Browser = await chromium.launch();

    const context = await browser.newContext({
        userAgent: 'Mozilla/5.0 (X11; Linux x86_64)',
        acceptDownloads: true
    });

    const page: Page = await context.newPage();
    await page.goto(process.argv[2]);

    await page.evaluate(() => window.scrollTo(0, document.body.scrollHeight / 2));

    await page.waitForSelector('#form-button-1086153590');
    await page.click('#onetrust-accept-btn-handler');

    const [download] = await Promise.all([
        page.waitForEvent('download'),
        page.click('#form-button-1086153590'),
      ]);
    await download.saveAs('../TEMP/AMDuprof.rpm');
    
    // not needed but I'd like to make sure that it finished downloading before we close it
    await new Promise(r => setTimeout(r, 1000));

    await context.close();
    await browser.close();
})();