function drawGrid(width, height, size) {
    //green lines
    stroke('green');
    strokeWeight(2);

    //vertical dividers
    for(let i = width/size; i < width; i+=width/size) {
        line(i,0,i,height);
    }

    //horizontal dividers
    for(let i = height/size; i < height; i+=height/size) {
        line(0,i,width,i);
    }
}
