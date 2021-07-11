let env = new environment(7, 5);
let player = 1;

function preload() {
}

function setup() {
    let canv = createCanvas(800,600);
    canv.parent("#canvas-container");
}

function draw() {
    background(225);
    env.draw_board();

    if(player == 1) fill('red');
    else fill('yellow');
    circle(mouseX,mouseY, 80);
}

function mouseClicked() {
    player = 3 - player; 
}
