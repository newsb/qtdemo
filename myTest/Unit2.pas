unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm2 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
    btn1: TButton;
    procedure Button1Click(Sender: TObject);
    procedure btn1Click(Sender: TObject);
  private
    { Private declarations }
function GetHWndByPID(const hPID: THandle): THandle;
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

{$R *.dfm}
     uses TLHelp32;

function EnumChildWndProc(AhWnd:LongInt; AlParam:lParam):boolean;stdcall;
var
	WndClassName: array[0..254] of Char;
	WndCaption: array[0..254] of Char;   s:String;
begin
	GetClassName(AhWnd,wndClassName,254);
	GetWindowText(aHwnd,WndCaption,254);
	with form2.memo1 do
	begin
		  lines.add(string(wndClassName));
		  lines.add(string(wndCaption));
	    lines.add('-------');
	end;


//  if {('Edit1'=WndCaption) and}('TEdit'=wndClassName)then
//   begin
//    form2.memo1.  lines.add(' found Edit1,send setText ');
//       //�������� AhWnd
////       SetWindowText(AhWnd,PAnsiChar('300'));
////       s:='333';
////      SendMessage(AhWnd,WM_SETTEXT,0,@s);  // Perform(, 0, string(Value))
//      SendMessage(AhWnd,WM_SETTEXT,0,Integer(pchar('*��ΪRichEdit20W�������ı�')));
//   end     ;

  if {('Button1'=WndCaption) and}('TButton'=wndClassName)then
   begin
   form2.memo1. lines.add(' found Button1,send click ');
       //�������� AhWnd
//       SendMessage(AhWnd,WM_LBUTTONDOWN,0,0);

        SetForegroundWindow(AhWnd);//���ô���Ϊ��ǰ����
        keybd_event(VK_RETURN,MapVirtualKey(VK_RETURN,0),0,0);
        sleep(1000);
   end     ;

  result:=true;
end;
function EnumChildWndProc2(AhWnd:LongInt; AlParam:lParam):boolean;stdcall;
var
	WndClassName: array[0..254] of Char;
	WndCaption: array[0..254] of Char;   s:String;
begin
	GetClassName(AhWnd,wndClassName,254);
	GetWindowText(aHwnd,WndCaption,254);
	with form2.memo1 do
	begin
		  lines.add(string(wndClassName));
		  lines.add(string(wndCaption));
	    lines.add('-------');
	end;


  if ('ȷ��'=WndCaption) and('TdyButton'=wndClassName)then
   begin
   form2.memo1. lines.add(' found Button1,send click ');
       //�������� AhWnd
//       SendMessage(AhWnd,WM_LBUTTONDOWN,0,0);

        SetForegroundWindow(AhWnd);//���ô���Ϊ��ǰ����
        keybd_event(VK_RETURN,MapVirtualKey(VK_RETURN,0),0,0);
        sleep(1000);
   end     ;

  result:=true;
end;


procedure TForm2.btn1Click(Sender: TObject);

var
  ProcessName : string; //������
  FSnapshotHandle:THandle; //���̿��վ��
  FProcessEntry32:TProcessEntry32; //������ڵĽṹ����Ϣ
  ContinueLoop:BOOL;
  MyHwnd:THandle;
begin
  FSnapshotHandle:=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); //����һ�����̿���
  FProcessEntry32.dwSize:=Sizeof(FProcessEntry32);
  ContinueLoop:=Process32First(FSnapshotHandle,FProcessEntry32); //�õ�ϵͳ�е�һ������
  //ѭ������
  while ContinueLoop do
  begin
    ProcessName := FProcessEntry32.szExeFile;

    if(ProcessName = 'Asco11.exe') then
    begin
      MyHwnd := GetHWndByPID(FProcessEntry32.th32ProcessID);
    //  ...
      Memo1.Lines.Add('found Handle :'+IntToStr(MyHwnd) +' (0x'+IntToHex(MyHwnd, 2)+')') ;

      EnumChildWindows(MyHwnd,@EnumChildWndProc2,0);

      Memo1.Lines.Add('  Handle IsVCLControl:'+BoolToStr( IsVCLControl(MyHwnd),True));
      break;
    //  ...
    end;
    ContinueLoop:=Process32Next(FSnapshotHandle,FProcessEntry32);
  end;
  CloseHandle(FSnapshotHandle);

end;

procedure TForm2.Button1Click(Sender: TObject);
var
  ProcessName : string; //������
  FSnapshotHandle:THandle; //���̿��վ��
  FProcessEntry32:TProcessEntry32; //������ڵĽṹ����Ϣ
  ContinueLoop:BOOL;
  MyHwnd:THandle;
begin
  FSnapshotHandle:=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); //����һ�����̿���
  FProcessEntry32.dwSize:=Sizeof(FProcessEntry32);
  ContinueLoop:=Process32First(FSnapshotHandle,FProcessEntry32); //�õ�ϵͳ�е�һ������
  //ѭ������
  while ContinueLoop do
  begin
    ProcessName := FProcessEntry32.szExeFile;

    if(ProcessName = 'Project1.exe') then
    begin
      MyHwnd := GetHWndByPID(FProcessEntry32.th32ProcessID);
    //  ...
      Memo1.Lines.Add('found Handle :'+IntToStr(MyHwnd) +' (0x'+IntToHex(MyHwnd, 2)+')') ;

      EnumChildWindows(MyHwnd,@EnumChildWndProc,0);

      Memo1.Lines.Add('  Handle IsVCLControl:'+BoolToStr( IsVCLControl(MyHwnd),True));
      break;
    //  ...
    end;
    ContinueLoop:=Process32Next(FSnapshotHandle,FProcessEntry32);
  end;
  CloseHandle(FSnapshotHandle); // �ͷſ��վ��
end;


//����ProcessId��ȡ���̵Ĵ��ھ��
function TForm2.GetHWndByPID(const hPID: THandle): THandle;
  type
    PEnumInfo = ^TEnumInfo;
    TEnumInfo = record
    ProcessID: DWORD;
    HWND: THandle;
  end;

  function EnumWindowsProc(Wnd: DWORD; var EI: TEnumInfo): Bool; stdcall;
    var
    PID: DWORD;
  begin
    GetWindowThreadProcessID(Wnd, @PID);
    Result := (PID <> EI.ProcessID) or
    (not IsWindowVisible(WND)) or
    (not IsWindowEnabled(WND));

    if not Result then EI.HWND := WND;
  end;

  function FindMainWindow(PID: DWORD): DWORD;
  var
    EI: TEnumInfo;
  begin
    EI.ProcessID := PID;
    EI.HWND := 0;
    EnumWindows(@EnumWindowsProc, Integer(@EI));
    Result := EI.HWND;
  end;
begin
  if hPID<>0 then
    Result:=FindMainWindow(hPID)
  else
    Result:=0;
end;

end.
