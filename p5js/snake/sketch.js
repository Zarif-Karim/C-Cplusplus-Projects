let canvas;
let score_tag;
let speed_tag;
let max_tag;
let startPause_btn;
let reset_btn;

let gridSize = 40; // gird(girdSize x gridSize)
let canvasSize = 600;

let grid;
let snake;
let food;
let score;
let nn;

let dead;
let speed;
let onFood;


function preload() {
    score_tag = select('#score-container');
    speed_tag = select('#speed-container');
    max_tag = select('#max-container');


    let options = [[32,'ReLu'],[32,'ReLu'],[4,'SoftMax']];
    nn = new Network(gridSize*gridSize+1,3,options)

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
    speed = 10;
    score = 0;
    onFood = false;

    speed_tag.html(speed);
    score_tag.html(score);    
    max_tag.html(score);
    

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
        speed = 10; 
        speed_tag.html(speed);
        score_tag.html(score);
        startPause_btn.html('Start');
        frameRate(speed);
        generateFood();
    });

    //speed of snake
    frameRate(speed);
    noLoop();
}

let retVal;
let agent_max_score = 0;

function draw() {
    background(0);

    snake.run();

    grid.step();
    retVal = {'nextState': grid.grid, 'reward': grid.stateScore(), 'done': dead};
    agent_max_score += retVal.reward;
    //console.log(agent_max_score);

    if(dead) {
        noLoop();
        max_tag.html(Math.max(int(max_tag.html()), score));
        agent_max_score = 0;
    }
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

class Snake {
    //moves: 'u','d','l','r'

    constructor(startX,startY, size) {
        this.head = createVector(startX+2, startY);
        this.length = 3;
        this.body = [createVector(this.head.x-2,this.head.y)]; // tail
        this.body.push(createVector(this.head.x-1,this.head.y)); //body
        this.body.push(createVector(this.head.x,this.head.y)); //head
        this.size = size;
        this.direction = 'r';
    }

    run() {
        this.move();
        //this.show();
        this.update();
    }

    show() {
        //body
        for(let i = 0; i < this.length - 1; i++) {
            grid.setGrid(this.body[i].x,this.body[i].y,1);
        }
        //head
        grid.setGrid(this.body[this.length].x,this.body[this.length].y,8);
    }

    move() {
        let dir = ['u','d','l','r'];
        let prediction = nn.predict([...grid.grid.flat(),dir.indexOf(this.direction)]);
        let pred_max = prediction.reduce(function(a,b){return Math.max(a,b);});
        console.log(dir[prediction.indexOf(pred_max)]);

        if (this.direction === 'r') this.head.y += 1;
        if (this.direction === 'l') this.head.y -= 1;
        if (this.direction === 'u') this.head.x -= 1;
        if (this.direction === 'd') this.head.x += 1;
    }

    randomMove() {
        validMoves = [];

        if (this.direction === 'r') validMoves.splice(0,1);
        if (this.direction === 'l') validMoves.splice(1,1);
        if (this.direction === 'u') validMoves.splice(2,1);
        if (this.direction === 'd') validMoves.splice(3,1);

        this.direction = validMoves[int(Math.random(0,4))];
    }

    update() {
        //move snake one grid towards direction
        grid.setGrid(this.body[0].x,this.body[0].y,0);
        grid.setGrid(this.body[this.length-1].x,this.body[this.length-1].y,8);

        dead = this.isDead();

        if(!this.eatingFood()) this.body.shift();
        this.body.push(createVector(this.head.x,this.head.y));

    }
    
    onFood() {
        if(this.head.x == food.x && this.head.y == food.y) {
            onFood = true;
        }
        else 
        onFood = false;

        return onFood;
    }

    eatingFood() {
        if(this.onFood()) {
            this.length += 1;
            score += 1;// console.log("score: ",score);
            generateFood();

            speed = int(map(score, 1,300,10,60));
            frameRate(speed);
            //console.log("speed: ",speed);

            speed_tag.html(speed);
            score_tag.html(score);

            return true;
        }

        return false;
    }

    setDirection(towards) {
        this.direction = towards;
    }

    isDead() {
        if( this.head.x < 0 || this.head.x >= gridSize ||
            this.head.y < 0 || this.head.y >= gridSize ||
            grid.getGrid(this.head.x, this.head.y) == 8) return true;

        return false;
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

    step() {
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

    stateScore() {
        if(dead) return -1000;
        else if(onFood) {
            onFood = false;
            return 100;
        }
        else return -1;
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

