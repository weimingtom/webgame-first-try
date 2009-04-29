package
{
  import flash.display.*;
  public class CustomCircle extends Shape
  {
    private var xPos:Number;
    private var yPos:Number;
    private var radius:Number;
    private var color:uint;
    public function CustomCircle(xInput:Number,
		yInput:Number,
		rInput:Number,
		colorInput:uint)
    {
      xPos = xInput;
      yPos = yInput;
      radius = rInput;
      color = colorInput;
      this.graphics.beginFill(color);
      this.graphics.drawCircle(xPos,yPos,radius);
    }
  }
}