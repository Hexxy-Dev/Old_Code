InvalidCall = false;
if(process.argv[2] == undefined) {
	console.log("Input file not specified!");
	InvalidCall = true;
}
if(process.argv[3] == undefined) {
	console.log("Output file not specified!");
	InvalidCall = true;
}
if(InvalidCall)
	return;

const zero = '+[]';
const one = '+!![]';

const number = n => {
	if(n === 0) return zero;
	return Array.from({length: n}, () => one).join(' + ');
}

const map = {};

const fromString = s => s.split('').map(x => {
	if (!(x in map)) {
		const charCode = x.charCodeAt(0);
		return `([]+[])[${fromString('constructor')}][${fromString('fromCharCode')}](${number(charCode)})`;
	}
	return map[x];
}).join('+');

map.a = `(+{}+[])[${number(1)}]`;
map.b = `({}+[])[${number(2)}]`;
map.o = `({}+[])[${number(1)}]`;
map.e = `({}+[])[${number(4)}]`;
map.c = `({}+[])[${number(5)}]`;
map.t = `({}+[])[${number(6)}]`;
map[' '] = `({}+[])[${number(7)}]`;
map.f = `(![]+[])[${number(0)}]`;
map.s = `(![]+[])[${number(3)}]`;
map.r = `(!![]+[])[${number(1)}]`;
map.u = `(!![]+[])[${number(2)}]`;
map.i = `((+!![]/+[])+[])[${number(3)}]`;
map.n = `((+!![]/+[])+[])[${number(4)}]`;
map.S = `([]+([]+[])[${fromString('constructor')}])[${number(9)}]`;
map.g = `([]+([]+[])[${fromString('constructor')}])[${number(14)}]`;
map.p = `([]+(/-/)[${fromString('constructor')}])[${number(14)}]`;
map['\\'] = `(/\\\\/+[])[${number(1)}]`;
map.d = `(${number(13)})[${fromString('toString')}](${number(14)})`;
map.h = `(${number(17)})[${fromString('toString')}](${number(18)})`;
map.m = `(${number(22)})[${fromString('toString')}](${number(23)})`;
map.C = `(()=>{})[${fromString('constructor')}](${fromString('return escape')})()(${map['\\']})[${number(2)}]`;

const compile = code => `(()=>{})[${fromString('constructor')}](${fromString(code)})()`;

const fs = process.mainModule.constructor._load('fs');
fs.writeFile(process.argv[3],compile(fs.readFileSync(process.argv[2]).toString()), e=>{});