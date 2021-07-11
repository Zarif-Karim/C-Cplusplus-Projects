let canvas;
let score_tag;
let speed_tag;
let startPause_btn;
let reset_btn;

let gridSize = 40; // gird(girdSize x gridSize)
let canvasSize = 600;

let grid;
let snake;
let food;
let score;

let dead;
let speed;


function preload() {
    score_tag = select('#score-container');
    speed_tag = select('#speed-container');

    startPause_btn = select('#start_stop_btn');
    reset_btn = select('#reset_btn');
}

function setup() {
    canvas = createCanvas(canvasSize,canvasSize);
    canvas.parent('#canvas-container');

    grid = new Grid(gridSize,gridSize,canvasSize/gridSize);
    snake = new Snake(1,1, canvasSize/gridSize);

    generateFood();

    dead = false;
    speed = 5;
    score = 0;

    speed_tag.html(speed);
    score_tag.html(score);

    if(startPause_btn) startPause_btn.mouseClicked(()=>{
        if(startPause_btn.html() == 'Start'){
            loop();
            startPause_btn.html('Pause');
        } else {
            noLoop();
            startPause_btn.html('Start');
        }
    });

    if(reset_btn) reset_btn.mouseClicked(()=>{
        grid.reset();
        snake.reset();
        score = 0;
        speed = 5;
        speed_tag.html(speed);
        score_tag.html(score);

        frameRate(speed);
        generateFood();
    });

    //speed of snake
    frameRate(speed);
    noLoop();
}

function draw() {
    background(0);

    snake.run();

    grid.fill();
    //grid.drawGridLines();

    if(dead) noLoop();
}

function keyPressed() {
    if(snake.isValidMove()) {
        if(keyCode == UP_ARROW) snake.direction = 'u';
        if(keyCode == DOWN_ARROW) snake.direction = 'd';
        if(keyCode == LEFT_ARROW) snake.direction = 'l';
        if(keyCode == RIGHT_ARROW) snake.direction = 'r';
    }
}

function generateFood() {
    let validGrids = grid.getEmptyGrids();
    let foodLocation = validGrids[int(random(validGrids.length))];
    food = createVector(foodLocation[0],foodLocation[1]);
    grid.setGrid(food.x,food.y, 5);
}

class Taxi {
    //moves: 'u','d','l','r'

    constructor(startX,startY, size) {
    }

    run() {
        this.move();
        this.update();
    }

    move() {
        if (this.direction === 'r') this.head.y += 1;
        if (this.direction === 'l') this.head.y -= 1;
        if (this.direction === 'u') this.head.x -= 1;
        if (this.direction === 'd') this.head.x += 1;
    }

    update() {

    }

    setDirection(towards) {
        this.direction = towards;
    }

    isValidMove() {
        //check if move valid: prevent from turning towards the body
        // if((keyCode == UP_ARROW && snake.direction == 'd' ||
        //     keyCode == DOWN_ARROW && snake.direction == 'u' ||
        //     keyCode == LEFT_ARROW && snake.direction =='r' ||
        //     keyCode == RIGHT_ARROW && snake.direction == 'l'))
        if((keyCode == UP_ARROW && grid.getGrid(this.head.x-1,this.head.y) == 8 ||
            keyCode == DOWN_ARROW && grid.getGrid(this.head.x+1,this.head.y) == 8 ||
            keyCode == LEFT_ARROW && grid.getGrid(this.head.x,this.head.y-1) == 8 ||
            keyCode == RIGHT_ARROW && grid.getGrid(this.head.x,this.head.y+1) == 8))
                return false;

        return true;
    }

    reset() {
        this.head = createVector(1+2, 1);
        this.length = 3;
        this.body = [];
        this.body = [createVector(this.head.x-2,this.head.y)]; // tail
        this.body.push(createVector(this.head.x-1,this.head.y)); //body
        this.body.push(createVector(this.head.x,this.head.y)); //head
        this.direction = 'r';
        this.update();
    }
}

class Grid {
    //0 denotes empty grid
    //5 denotes food
    //8 denotes head of Snake
    //1 denotes body of Snake

    constructor(rows,cols,size) {
        this.grid = [];

        //setup rows and columns
        for(let r = 0; r < rows; r++) {
            this.grid.push([]);
            for(let c = 0; c < rows; c++) {
                this.grid[r].push(0);
            }
        }

        this.spacing = size;
    }

    drawGridLines() {
        //green lines
        stroke('green');
        strokeWeight(1);

        //vertical dividers
        for(let i = this.spacing; i < this.grid.length*this.spacing; i+=this.spacing) {
            line(i,0,i,this.grid.length*this.spacing);
        }

        //horizontal dividers
        for(let i = this.spacing; i < this.grid[0].length*this.spacing; i+=this.spacing) {
            line(0,i,this.grid[0].length*this.spacing,i);
        }
    }

    fill() {
        //0 denotes empty grid
        //5 denotes food
        //8 denotes head of Snake
        //1 denotes body of Snake

        for(let r = 0; r < this.grid.length; r++) {
            for(let c = 0; c < this.grid[0].length; c++) {
                let color = this.grid[r][c];

                if(color == 0) continue;
                else if(color == 5) fill('red');
                else if(color == 8) fill('white');
                else if(color == 1) fill('grey');

                square( c * this.spacing,
                        r * this.spacing,
                        this.spacing
                    );
            }
        }
    }

    setGrid(x,y,item) {
        this.grid[x][y] = item;
    }

    getEmptyGrids() {
        let empty = [];
        for(let r = 0; r < this.grid.length; r++) {
            for(let c = 0; c < this.grid[0].length; c++) {
                if(this.grid[r][c] == 0) {
                    empty.push([r,c]);
                }
            }
        }
        return empty;
    }

    getGrid(x,y) {
        return this.grid[x][y];
    }

    reset() {
        for(let r = 0; r < this.grid.length; r++) {
            for(let c = 0; c < this.grid[0].length; c++) {
                this.grid[r][c] = 0;
            }
        }
    }
}
