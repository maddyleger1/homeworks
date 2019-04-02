import React from 'react';
import ReactDOM from 'react-dom';
import { Button, Container, Row, Col } from 'reactstrap';

export default function run_demo(root) {
  ReactDOM.render(<Demo />, root);
}

class Demo extends React.Component {
	
	constructor(props) {
		super(props);
		this.state = { 
			moves: 0,
			won: false,	
			isRevealed: Array(16).fill(false),
			isMatched: Array(16).fill(false),
			tiles: this.randomizeLetters(),		
		};
  	}

	reset () {
		this.setState({
			moves: 0,
			won: false,
			isRevealed: Array(16).fill(false),
			isMatched: Array(16).fill(false),
			tiles: this.randomizeLetters(),
		});
	}

	randomizeLetters () {
		let letters = new String("AABBCCDDEEFFGGHH");
		let tiles = letters.split('');
		tiles = _.shuffle(tiles);
		return tiles;
	}

	handleClick(i) {
		const reveal = this.state.isRevealed.slice();
		reveal[i] = true;
		const matched = this.state.isMatched.slice();
		let moves = this.state.moves + 1;
		this.setState({isRevealed: reveal, moves: moves});
		this.render();
	
		const reveal2 = reveal.slice();

		const flipped = _.filter(reveal2, function(match) {
			if (match) return match;
		});

		// even number of tiles flipped = this is the 2nd
		if (flipped.length > 0 && flipped.length % 2 == 0) {
			// check if the one currently revealed matches another revealed
			let pair_index = null;
			for (let j=0; j<16; j++) {
				if (this.state.tiles[i] == this.state.tiles[j]) {
					if (i != j) { pair_index = j }
				}
			}

			// if it does, mark them both as matched
			if (reveal2[pair_index]) {
				matched[i] = true;
				matched[pair_index] = true;
			}
			// if it doesnt, flip this one
			else {
				reveal2[i] = false;
			}
			// find the other "unmatched but flipped" one, and flip that too
			for (let j=0; j<16; j++) {
				if (reveal2[j] && !matched[j]) {
					reveal2[j] = false;
				}
			}
			setTimeout(() => {
				this.setState(
					{isRevealed: reveal2, 
						isMatched: matched,
						won: this.checkWin()
					});
			}, 1000);
		}
	}

	checkWin() {
		if (!(_.contains(this.state.isRevealed, false))) 
			return true;
		else
			return false;
	}
	
	render() {
    	return (
			<div className="container">
				<div className="row">
					<p>{this.state.won ? "You won! Click Reset to Play Again" : ""}</p>
				</div>
				<div className="row">
					<p>Moves: {this.state.moves}</p>
				</div>
				<div className="row">
					<TileBoard tiles={this.state.tiles}
						isRevealed={this.state.isRevealed}
						isMatched={this.state.isMatched}
						onClick={i => this.handleClick(i)}
					/>
				</div>
				<div className="row">
					<button type="button" 
					className={"btn btn-secondary btn-block"} 
					onClick={() => this.reset()}>Reset
					</button>
				</div>
			</div>
    	);
  	}
}

class Tile extends React.Component {
	render() {
        return (
			<button type="button"
				className={"btn " + (this.props.value != "?" ? this.props.color : "btn-primary") + " tile"} 
				onClick={() => this.props.onClick()}>
    	            {this.props.value}
            </button>
        );  
    }
}

class TileBoard extends React.Component {
	
	renderTile(i) {
		return <Tile 
			value={this.props.isRevealed[i] ? this.props.tiles[i] : "?"} 
			onClick={() => this.props.onClick(i)} 
			color={ this.props.isMatched[i] ? "btn-success" : "btn-warning" }
		/>;
    }

    render() {
        return (
            <div>
                <div className="status">{status}</div>
                <div className="tile-row">
					{this.renderTile(0)}
					{this.renderTile(1)}
                    {this.renderTile(2)}
                    {this.renderTile(3)}
                </div>
                <div className="tile-row">
                    {this.renderTile(4)}
                    {this.renderTile(5)}
                    {this.renderTile(6)}
                    {this.renderTile(7)}
                </div>
                <div className="tile-row">
                    {this.renderTile(8)}
                    {this.renderTile(9)}
                    {this.renderTile(10)}
                    {this.renderTile(11)}
                </div>
                <div className="tile-row">
                    {this.renderTile(12)}
                    {this.renderTile(13)}
                    {this.renderTile(14)}
                    {this.renderTile(15)}
                </div>
            </div>
        );
    }
}
