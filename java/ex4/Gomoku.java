import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;

public class Gomoku extends GomokuDraw {
	boolean flag;
	double click_range;

	public Gomoku()
	{
		flag = false;
		setClickRange(this.grid_width * 3.34/10.0);
		canvas.setOnMouseClicked(new Message(this));
	}

	public void handle(MouseEvent event)
	{
		int c[]=click(event.getX(), event.getY());
		if ( c == null )
			return;
		setChessman(c[0], c[1], flag);
		flag = flag ? false : true;
	}

	public Gomoku setClickRange(double d)
	{
		this.click_range = d;
		return this;
	}

	int[] click(double cx, double cy)
	{
		int row, col;
		int c[] = new int[2];
		if (cx < this.chessboard_startX-this.click_range || cx > this.chessboard_endX+this.click_range)
			return null;
		if (cy < this.chessboard_startY-this.click_range || cy > this.chessboard_endY+this.click_range)
			return null;
		cx -= this.chessboard_startX;
		cy -= this.chessboard_startY;
		row = (int) ( cy / this.grid_height );
		col = (int) ( cx / this.grid_width );
		if ( cx % this.grid_width > this.grid_width - this.click_range )
			++col;
		else if ( cx % this.grid_width > this.click_range )
				return null;
		if ( cy % this.grid_height > this.grid_height - this.click_range )
			++row;
		else if ( cy % this.grid_height > this.click_range )
				return null;
		c[0]=row;
		c[1]=col;
		return c;
	}

	class Message implements EventHandler<MouseEvent>
	{
		Gomoku gomoku;

		public Message(Gomoku gomoku)
		{
			this.gomoku = gomoku;
		}

		public void handle(MouseEvent event)
		{
			gomoku.handle(event);
		}
	}
}
