let heading = document.getElementById("heading");
// heading.append(" by Vatsal");
let boxes = document.querySelectorAll(".box");
let count = 0;
// for (box of boxes) {
//   box.innerText = count++;
// }

let id = boxes[0].getAttribute("id");
console.log(id);
boxes[0].setAttribute("name", "first");

heading.style.backgroundColor = "dodgerblue";

let button = document.createElement("button");
button.innerText = "I am button";
boxes[1].append(button);

let pre = document.querySelector("pre");
pre.remove();

let btn = document.querySelector("#btn");
btn.onclick = (e) => {
	console.log(e.clientX, e.clientY, e.target);
}

let mode = document.createElement("button");
mode.innerText = "Change Theme";
boxes[2].after(mode);
let body = document.querySelector("body");
const change = () => {
  console.log("clicked");
  if (body.style.backgroundColor == "cyan") body.style.backgroundColor = "darkblue";
  else body.style.backgroundColor = "cyan";
}
mode.addEventListener("click", change);
