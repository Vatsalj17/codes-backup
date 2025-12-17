let url = "http://api.openweathermap.org/data/2.5/weather?q=varanasi&appid=e6d43eafcf69f246c6180b997c652ea7&units=metric";

let para = document.querySelector("#data");
let btn = document.querySelector("#btn");

const getdata = async () => {
  let response = await fetch(url);
  console.log(response);
  let data = await response.json();
  console.log(data);
  para.innerText = data;
};

btn.addEventListener("click", getdata);
