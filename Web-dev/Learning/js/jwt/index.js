import jwt from "jsonwebtoken"

// const user = {
//   name:"vatsal"
// }
// const token = jwt.sign(user,"bendoch",{expiresIn: "10m"});
const generated_token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJuYW1lIjoidmF0c2FsIiwiaWF0IjoxNzU3MjYzOTA2LCJleHAiOjE3NTcyNjQ1MDZ9.cM9VVzMiJY02CS1YvCK2Wc-AI2Le2PWYnzLDekuriwI"
const decode = jwt.verify(generated_token, "bendoch")
const time = new Date(decode.exp).getHours()
console.log(time)
console.log(decode);
