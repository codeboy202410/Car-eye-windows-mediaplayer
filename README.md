# car-eye-windows-player

Car-eye-windows player 比较简单，看相关代码即可，内部集成的文档



CarEye windows插件使用说明
1.	ActiveX OCX控件
ActiveX控件使用MFC ActiveX框架生成非常简单，这里就不做过多赘述，感兴趣的同学可以下载CarEyePlayer源码；注意，IE11已经不支持AttachEvent的方式触发浏览器页面事件，所以，需要导出播放事件的同学在前端页面编写的时候需要做好IE11的兼容性处理；
2.	npAPI插件 npAPI插件由FireBreath框架生成，该框架提供了非常详细的步骤即可生成我们想要的播放器插件框架，框架生成好以后将EasyPlayer源码的CarEyePlayerPlugin目录下的代码替换掉生成的代码即可。
3.	插件导出接口说明
[1]	LONG Start(LPCTSTR sURL, LPCTSTR sRenderFormat, LPCTSTR sUserName, LPCTSTR sPassword, LPCTSTR sHardDecord);

Start函数对CarEyePlayer_OpenStream函数进行了封装，其作用是打开一个RTSP流；
参数说明： [sURL]：打开的流地址，以rtsp://开头； [sRenderFormat]：播放渲染格式，枚举对应格式： D3D支持格式如下： YV12: 0 YUY2: 1 UYVY: 2 A8R8G8B8: 3 X8R8G8B8: 4 RGB565: 5 RGB555: 6 GDI支持格式: RGB24: 7 [sUserName]: RTSP流验证用户名,如果流URL里面已经包含, 这里填空; [sPassword]: RTSP流验证密码,如果流URL里面已经包含, 这里填空; [sHardDecord]: 是否使用硬件解码， 0=软解 1=硬解
注意：OCX接口函数所有参数均为字符串类型，主要是为了方便页面js调用，下面所有接口参数皆是如此；
[2]	void Config(LPCTSTR sFrameCache, LPCTSTR sPlaySound, LPCTSTR sShowToScale, LPCTSTR sShowStatisticInfo);
Config函数配置播放器的一些参数，诸如缓存，是否播放音频，是否按比列显示，是否显示码率信息； 参数说明： [sFrameCache]：缓存帧数，1-n ，该数值越小，延时越小，当然播放画面可能再网络带宽不理想的情况下会比较卡，反之则延时越大，相应的播放也会比较流畅； [sPlaySound]：是否播放音频，1=播放，0=不播放 [sShowToScale]：是否按比列显示，1=是 0=否 ，软解码时有效 [sShowStatisticInfo]：是否显示码率信息，1=是 0=否 ，软解码时有效
[3]	void SetOSD(LPCTSTR show, LPCTSTR alpha, LPCTSTR red, LPCTSTR green, LPCTSTR blue, LPCTSTR left, LPCTSTR top, LPCTSTR right, LPCTSTR bottom, LPCTSTR strOSD);
SetOSD是新增接口，用于设置视频显示时的OSD显示; 参数说明： [show]：是否显示OSD，1=显示 0=不显示 [alpha]：OSD显示叠加透明度， 0-255，0是完全透明。255完全不透明 [red]：OSD字幕颜色RGB分量中的R分量， [green]：OSD字幕颜色RGB分量中的G分量， [blue]：OSD字幕颜色RGB分量中的B分量， [left]：OSD基于视频的显示位置坐标的左上角x轴坐标 [top]：OSD基于视频的显示位置坐标的左上角y轴坐标 [right]：OSD基于视频的显示位置坐标的右下角x轴坐标 [bottom]：OSD基于视频的显示位置坐标的右下角y轴坐标 [strOSD]：OSD字幕
[4] void Close(void); Close关闭Start打开的流；
注意目前ActiveX控件定义一个控件初始化一个唯一的CarEyePlayer播放器实例，一个Start对应一个Close函数；Start函数只能调用一次，下一次调用时必然是先Cose，再Start； 4. WEB网页端调用 我们已经了解了插件的导出接口，那么我们就可以很容易的编写JS来实现网页端的播放啦，当然，在此之前，我们需要注册一下插件，在CarEyePlayer目录下有reg.bat和np_reg.bat批处理文件分别对OCX和npAPI进行注册，提示注册成功后即可使用。
在CarEyePlayer的bin目录下我们已经提供了两个Demo html页面供大家测试和使用，JS代码很简单，直接调用即可：
		function config(){
		var obj = document.getElementById("CarEyePlayerOcx");

		var cache = document.getElementById("cache").value;
		var playsound = document.getElementById("playsound").value;
		var showtoscale= document.getElementById("showtoscale").value;
		var showsatic = document.getElementById("showsatic").value;

		obj.Config(cache, playsound, showtoscale, showsatic);
				
		//alert(cache+";"+playsound+";"+showtoscale+";"+showsatic);

	}

	function startplay(){
		var obj = document.getElementById("CarEyePlayerOcx");
		var url = document.getElementById("url").value;
		var rendertype = document.getElementById("rendertype").value;
		var name= document.getElementById("name").value;
		var password = document.getElementById("password").value;
		var hardDecode = document.getElementById("hardwareDecode").value;
		

		obj.Start(url, rendertype, name, password,hardDecode);
		config();

		//alert(url+";"+rendertype+";"+name+";"+password);

	}

		function stopplay(){
		//alert("Close()!!!!!");
		var obj = document.getElementById("CarEyePlayerOcx");

		obj.Close();
	}

