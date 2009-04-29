package
{
  import flash.display.*;
  //牢记显示对象构成的层次结构
  public class CustomCircle extends Sprite
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