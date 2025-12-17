const getPromise = () => {
  return new Promise((resolve, reject) => {
    console.log("I am Promise");
    resolve("resolve ho gaya");
    // reject("lag gaye");
  })
}

let promise = getPromise();
promise.then((res) => {
  console.log("Promise fulfilled", res);
}).catch((err) => {
    console.log("Promise rejected", err);
  })
