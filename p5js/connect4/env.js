
//environment

class environment {
    constructor(_size_row, _size_col) {
        this.game = "Connect 4";
        this.row = _size_row;
        this.col = _size_col; 

        this.grid = new Array(this.row);
        for(let i = 0; i < this.grid.length; i++) {
            this.grid[i] = new Array(this.col);
            for(let j = 0; j < this.col; j++) {    
                this.grid[i][j] = 0;
            } 
        }
    }

    step(player, x , y) {
        this.grid[x][y] = player;
    }

    draw_board() {
        fill('blue');

        rect(50,100, 100 * this.row, 100 * this.col);
    }
}