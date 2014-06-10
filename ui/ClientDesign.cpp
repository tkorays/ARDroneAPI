#include "ClientDesign.h"
#include "MainWindow.h"
#include "WindowEvents.h"
#include "AppConfig.h"


const long ClientDesign::ID_WIN_BANNER = 4;
const long ClientDesign::ID_VIDEO_PLAYER = 5;

ClientDesign::ClientDesign(wxWindow* parent){
	app_config config;
	/*
	long splitwin_style = wxSP_3DBORDER | wxSP_3DSASH | wxSP_NO_XP_THEME | wxNO_BORDER;
	wxSplitterWindow* spwin = new wxSplitterWindow(parent, wxID_ANY, wxDefaultPosition, config.size, splitwin_style);
	//spwin->SetMinimumPaneSize(0);


	wxSplitterWindow* lwin = new wxSplitterWindow(spwin, wxID_ANY, wxDefaultPosition, wxSize(config.left_client_width, config.size.GetHeight()), wxSP_NO_XP_THEME | wxNO_BORDER);
	wxSplitterWindow* rwin = new wxSplitterWindow(spwin, wxID_ANY, wxDefaultPosition, wxSize(config.right_client_width, config.size.GetHeight()), wxSP_NO_XP_THEME | wxNO_BORDER);

	spwin->SplitVertically(lwin, rwin, 500);
	*/

	//parent->SetTransparent(245);

	// 底层
	wxBoxSizer* clientBox = new wxBoxSizer(wxVERTICAL);

	wxPanel* clientPanel = new wxPanel(parent);
	clientPanel->SetBackgroundColour(*wxWHITE);
	clientPanel->SetSizer(clientBox);
	clientPanel->SetSize(config.size);
	
	
	wxPanel* bannerPanel = new wxPanel(clientPanel, ID_WIN_BANNER, wxDefaultPosition, wxSize(config.size.GetWidth(), 30));
	bannerPanel->SetBackgroundColour(wxColor(123,123,123));
	bannerPanel->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MainWindow::OnLeftDown), NULL, parent);
	bannerPanel->Connect(wxEVT_MOTION, wxMouseEventHandler(MainWindow::OnLeftDrag), NULL, parent);
	bannerPanel->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainWindow::OnLeftUp), NULL, parent);
	wxPanel* mainPanel = new wxPanel(clientPanel,-1,wxPoint(0,30),wxSize(config.size.GetWidth(),config.size.GetHeight()-30));
	mainPanel->SetBackgroundColour(*wxWHITE);
	
	clientBox->Add(bannerPanel,0,wxEXPAND);
	clientBox->Add(mainPanel,0,wxEXPAND|wxALL);
	
	// 在bannerPanel里面加按钮以及caption
	wxBoxSizer* bannerBox = new wxBoxSizer(wxHORIZONTAL);
	bannerPanel->SetSizer(bannerBox);
	wxBoxSizer* caption = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* closeButton = new wxBoxSizer(wxHORIZONTAL);
	bannerBox->Add(caption);
	bannerBox->Add(closeButton);
	wxStaticText* captionText = new wxStaticText(bannerPanel, wxID_ANY, config.title, wxPoint(10, 5), wxSize(100, 30));
	captionText->SetForegroundColour(wxColor(225,225,225));
	caption->Add(captionText);
	wxStaticText* closeText = new wxStaticText(bannerPanel, wxID_EXIT, "X", wxPoint(config.size.GetWidth() - 30, 5), wxSize(30, 30));
	closeText->SetForegroundColour(*wxWHITE);
	closeButton->Add(closeText);
	closeText->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(WindowEvents::OnCloseButton), NULL, parent);
	

	// 接下来设计主界面
	wxBoxSizer* mainBox = new wxBoxSizer(wxHORIZONTAL);
	mainPanel->SetSizer(mainBox);
	wxBoxSizer* leftBox = new wxBoxSizer(wxVERTICAL); // 左侧的容器
	wxBoxSizer* rightBox = new wxBoxSizer(wxVERTICAL); // 右侧的容器
	mainBox->Add(leftBox); // 添加左侧容器
	mainBox->Add(rightBox); // 添加右侧容器
	// 左侧容器中添加一个视频播放窗口以及视频选项
	
	wxImage* img = new wxImage("img.png", wxBITMAP_TYPE_PNG);
	img->Resize(wxSize(640, 360),wxPoint(0,0));
	wxStaticBitmap* video = new wxStaticBitmap(mainPanel, ID_VIDEO_PLAYER,wxNullBitmap,wxDefaultPosition);
	video->SetBitmap(*img);
	leftBox->Add(video , 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	// 下面添加一些操作选项，这里用一个staticbox
	wxStaticBoxSizer* operation = new wxStaticBoxSizer(wxHORIZONTAL,mainPanel,_T("操作选项"));
	operation->SetMinSize(wxSize(630, 230));
	wxButton* bt_tmp = new wxButton(mainPanel, wxID_ANY, "OK");
	operation->Add(bt_tmp, 0, wxALIGN_LEFT | wxALL, 5);
	leftBox->Add(operation, 0, wxALIGN_LEFT | wxALL, 5);

	leftBox->Fit(mainPanel);

	// 右侧设计
	wxStaticBoxSizer* flystatus = new wxStaticBoxSizer(wxVERTICAL,mainPanel,_T("飞行状态"));
	wxStaticBoxSizer* ardronestatus = new wxStaticBoxSizer(wxVERTICAL, mainPanel, _T("ardrone状态"));

	// roll
	wxBoxSizer* roll_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* roll_label = new wxStaticText(mainPanel, wxID_ANY, _T("Roll:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* roll_value = new wxStaticText(mainPanel, wxID_ANY, _T("+0.0000"), wxPoint(0, 0), wxSize(110, 30));
	roll_box->Add(roll_label);
	roll_box->Add(roll_value);
	flystatus->Add(roll_box);

	// pitch
	wxBoxSizer* pitch_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* pitch_label = new wxStaticText(mainPanel, wxID_ANY, _T("Pitch:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* pitch_value = new wxStaticText(mainPanel, wxID_ANY, _T("+0.0000"), wxPoint(0, 0), wxSize(110, 30));
	pitch_box->Add(pitch_label);
	pitch_box->Add(pitch_value);
	flystatus->Add(pitch_box);

	// yaw
	wxBoxSizer* yaw_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* yaw_label = new wxStaticText(mainPanel, wxID_ANY, _T("Yaw:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* yaw_value = new wxStaticText(mainPanel, wxID_ANY, _T("+0.0000"), wxPoint(0, 0), wxSize(110, 30));
	yaw_box->Add(yaw_label);
	yaw_box->Add(yaw_value);
	flystatus->Add(yaw_box);

	// gaz
	wxBoxSizer* gaz_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* gaz_label = new wxStaticText(mainPanel, wxID_ANY, _T("Gaz:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* gaz_value = new wxStaticText(mainPanel, wxID_ANY, _T("+0.0000"), wxPoint(0, 0), wxSize(110, 30));
	gaz_box->Add(gaz_label);
	gaz_box->Add(gaz_value);
	flystatus->Add(gaz_box);

	
	// 已连接
	wxBoxSizer* connect_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* connect_label = new wxStaticText(mainPanel, wxID_ANY, _T("已连接:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* connect_value = new wxStaticText(mainPanel, wxID_ANY, _T("否"), wxPoint(0, 0), wxSize(110, 30));
	connect_box->Add(connect_label);
	connect_box->Add(connect_value);
	ardronestatus->Add(connect_box);

	// 电量
	wxBoxSizer* battery_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* battery_label = new wxStaticText(mainPanel, wxID_ANY, _T("电量:"),wxPoint(0,0),wxSize(110,30));
	wxStaticText* battery_value = new wxStaticText(mainPanel, wxID_ANY, _T("N/A"), wxPoint(0, 0), wxSize(110, 30));
	battery_box->Add(battery_label);
	battery_box->Add(battery_value);
	ardronestatus->Add(battery_box);

	// 高度
	wxBoxSizer* altitude_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* altitude_label = new wxStaticText(mainPanel, wxID_ANY, _T("高度:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* altitude_value = new wxStaticText(mainPanel, wxID_ANY, _T("N/A"), wxPoint(0, 0), wxSize(110, 30));
	altitude_box->Add(altitude_label);
	altitude_box->Add(altitude_value);
	ardronestatus->Add(altitude_box);

	// 飞行
	wxBoxSizer* flying_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* flying_label = new wxStaticText(mainPanel, wxID_ANY, _T("飞行中:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* flying_value = new wxStaticText(mainPanel, wxID_ANY, _T("否"), wxPoint(0, 0), wxSize(110, 30));
	flying_box->Add(flying_label);
	flying_box->Add(flying_value);
	ardronestatus->Add(flying_box);

	// 悬停
	wxBoxSizer* hovering_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* hovering_label = new wxStaticText(mainPanel, wxID_ANY, _T("悬停中:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* hovering_value = new wxStaticText(mainPanel, wxID_ANY, _T("否"), wxPoint(0, 0), wxSize(110, 30));
	hovering_box->Add(hovering_label);
	hovering_box->Add(hovering_value);
	ardronestatus->Add(hovering_box);

	// emergency
	wxBoxSizer* emergency_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* emergency_label = new wxStaticText(mainPanel, wxID_ANY, _T("Emergency:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* emergency_value = new wxStaticText(mainPanel, wxID_ANY, _T("否"), wxPoint(0, 0), wxSize(110, 30));
	emergency_box->Add(emergency_label);
	emergency_box->Add(emergency_value);
	ardronestatus->Add(emergency_box);

	// 视频帧率
	wxBoxSizer* frate_box = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* frate_label = new wxStaticText(mainPanel, wxID_ANY, _T("视频帧率:"), wxPoint(0, 0), wxSize(110, 30));
	wxStaticText* frate_value = new wxStaticText(mainPanel, wxID_ANY, _T("否"), wxPoint(0, 0), wxSize(110, 30));
	frate_box->Add(frate_label);
	frate_box->Add(frate_value);
	ardronestatus->Add(frate_box);

	ardronestatus->Fit(mainPanel);

	rightBox->Add(flystatus, 0, wxALIGN_LEFT | wxALL, 5);
	rightBox->Add(ardronestatus, 0, wxALIGN_LEFT | wxALL, 5);

	rightBox->Fit(mainPanel);
	mainBox->Fit(mainPanel);
}