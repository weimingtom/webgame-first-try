package
{
  import flash.display.Sprite;
  import flash.events.*;
  import flash.net.*;
  import flash.events.MouseEvent;

  public class main extends Sprite
  {
    private var dragshape:CustomCircle;

    public function main()
    {
      //创造一个可拖拽的对象
      dragshape = new CustomCircle(10,10,100,0xFFCC00);
      dragshape.addEventListener(MouseEvent.MOUSE_DOWN,startDragging);
      dragshape.addEventListener(MouseEvent.MOUSE_UP,stopDragging);
      this.addChild(dragshape);

      /*
      //绘制自定义的图形,并添加到Sprite里
      var circle1:CustomCircle = new CustomCircle(10,10,100,0xFFCC00);
      this.addChild(circle1);
      var circle2:CustomCircle = new CustomCircle(100,100,100,0xFF0000);
      this.addChild(circle2);
      var circle3:CustomCircle = new CustomCircle(140,140,100,0xFF00FF);
      this.addChild(circle3);
      //交换图形的层
      this.swapChildrenAt(0,1);
*/
      //在Sprite上填充的颜色
      this.graphics.lineStyle(2,0x00CC00);
      this.graphics.beginFill(0x0000AA);
      this.graphics.moveTo(0,0);
      this.graphics.lineTo(10,0);
      this.graphics.lineTo(10,10);
      this.graphics.lineTo(0,10);
      this.graphics.endFill();

      //使用URLRequest,URLLoader对象读取URL数据
      var request:URLRequest = new URLRequest("Debugger.as");
      var loader:URLLoader = new URLLoader();
      loader.addEventListener(Event.COMPLETE,completeHandler);
      try
      {
        loader.load(request);
      }
      catch(error:Error)
      {
        //Debugger.echo("Unable to load URL: " + error,this);
      }
    }

    private function completeHandler(event:Event):void
    {
      //Debugger.echo("loaderCompleteHandler called"+event.target.data,this);
    }

    private function startDragging(event:MouseEvent):void
    {dragshape.startDrag();}

    private function stopDragging(event:MouseEvent):void
    {dragshape.stopDrag();}
  }
}