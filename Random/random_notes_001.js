function HMM() {
	this.hmm = "NOOM";
}

HMM.prototype.SayIt = function() {
	console.log(this.hmm);
};

const h = new HMM();
h.SayIt(); // "NOOM"

console.log(h instanceof HMM); // true
console.log(typeof h); // "object"


class HMM2 {
	constructor() {
  	this.hmm = "NOOM2";
  }
  
  SayIt() {
  	(()=>{
    	console.log(this.hmm);
    })() // this keyword works in anon funcs
    const opa = function(){
    	console.log(this.hmm);
    }.bind(this); // this is needed if we use fuction instead of arrow
    opa();
  }
}

const h2 = new HMM2();
h2.SayIt(); // "NOOM2"
            // "NOOM2"

console.log(h2 instanceof HMM); // false
console.log(h2 instanceof HMM2); // true

/*
const and let are block scoped
var is hoisted
hoistig is automatic reordering of code to prevent "this X is not defined"
so we can call f() before function f() is defined as it is hoisted up to the top of the file
same with var
*/

console.log(hmm) // undefined
{
var hmm = 3; // hmm is accessible globally but it is assigned when we get to this block
}
console.log(hmm) // 3

/*
fetch("URL")
	.then(console.log) // this will work
  .catch(console.error)
  .finally(()=>{
  	//always execute
  })

new Promise((resolve, reject) => {
	resolve('g');
});
// resolve calls .then
// reject calls .catch

async function func() {
	try {
  	const result = await fetch("URL");
    console.log(result);
  } catch (e) {
  	console.error(e);
	} finally {
  
  }
}//*/

// to make object actually const use this
const obj = Object.freeze({
	name:"HMM"
});
// normally just the object is const not it's members


function counter() {
	let c = 0;
  return () => { // this is a clojure
  	return c++;				// aka external func that has access to local var
  }
}
const cou = counter();
console.log(cou()); // 0
console.log(cou()); // 1

/*
crud rest endpoints
HTTP REST
GET   //get data
POST  //create new data
PUT   //override data
PATCH //update specific data
*/
