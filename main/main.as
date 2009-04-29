package
{
  import flash.display.Sprite;
  import flash.events.*;
  import flash.net.*;

  public class main extends Sprite
  {
    public function main()
    {
      var request:URLRequest = new URLRequest("Debugger.as");
      var loader:URLLoader = new URLLoader();
      loader.addEventListener(Event.COMPLETE,completeHandler);
      try
      {
        loader.load(request);
      }
      catch(error:Error)
      {
        Debugger.echo("Unable to load URL: " + error,this);
      }
    }

    private function completeHandler(event:Event):void
    {
      Debugger.echo("loaderCompleteHandler called"+event.target.data,this);
    }
  }
}