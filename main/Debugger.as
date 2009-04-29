package
{
 public class Debugger
  {
      import flash.display.*;
      import flash.text.TextField;
      public static function echo(info:String,sprite:Sprite):void 
      { 
	try
	{
	   var myText:TextField = new TextField();
           myText.text = info;
           sprite.addChild(myText);
	}
	catch(e:Error){} 
      }
  }

}