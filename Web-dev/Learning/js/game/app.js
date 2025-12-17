let userScore = 0;
let compScore = 0;

const choices = document.querySelectorAll(".choice");
const msg = document.querySelector("#msg");

const userScoreDisplay = document.querySelector("#user-score");
const compScoreDisplay = document.querySelector("#comp-score");

const genCompChoice = () => {
  const options = ["rock", "paper", "scissors"];
  const randIdx = Math.floor(Math.random() * 3);
  return options[randIdx];
}

const drawGame = () => {
  console.log("game was draw");
  msg.innerText = "Draw! Play Again :)";
  msg.style.backgroundColor = "#081b31";
}

const showWinner = (userWin, userChoice, compChoice) => {
  if (userWin) {
    userScore++;
    userScoreDisplay.innerText = userScore;
    console.log("user won");
    msg.innerText = `You Win! ${userChoice} beats ${compChoice}`;
    msg.style.backgroundColor = "green";
  } else {
    compScore++;
    compScoreDisplay.innerText = compScore;
    console.log("computer won");
    msg.innerText = `You Lose! ${compChoice} beats ${userChoice}`;
    msg.style.backgroundColor = "red";
  }
}

const playGame = (userChoice) => {
  const compChoice = genCompChoice();
  console.log("user choice = ", userChoice);
  console.log("comp choice = ", compChoice);
  if (userChoice === compChoice) {
    drawGame();
  } else {
    let userWin = true;
    if (userChoice === "rock") userWin = compChoice === "paper" ? false : true;
    else if (userChoice === "paper") userWin = compChoice === "scissors" ? false : true;
    else userWin = compChoice === "rock" ? false : true;
    showWinner(userWin, userChoice, compChoice);
  }
}

choices.forEach((choice) => {
  choice.addEventListener("click", () => {
    const userChoice = choice.getAttribute("id");
    playGame(userChoice);
  })
})
