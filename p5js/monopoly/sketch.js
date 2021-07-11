function preload() {

}

function setup() {
    let canv = createCanvas(800,600,WEBGL);
    canv.parent("#canvas-container");
}

function draw() {
    background(130);

    //translate(-200,2.5);
    // box(400,5,400);
    plane(400,400);
}