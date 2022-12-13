#pragma once
#include <string>
#include <Windows.h>
#define WM_KOMOREBI_EVENT (WM_USER+1)

struct JsonKeyword {
    using string = std::string;
    //static const std::string 

    static const std::string event;
    static const std::string state;

};
#ifdef __ADD_KOMOREBI_HEADER_IMPL__

const std::string JsonKeyword::event = "event";
const std::string JsonKeyword::state = "state";


#endif


struct KomorebiEvent {

    static const std::string KomorebiConnect;
    static const std::string KomorebiUpdate;
    static const std::string KomorebiDisconnect;
    static const std::string FocusWorkspaceNumber;
    static const std::string FocusMonitorWorkspaceNumber;
    static const std::string FocusChange;
    static const std::string ChangeLayout;
    static const std::string ToggleTiling;
    static const std::string ToggleMonocle;
    static const std::string ToggleMaximise;
    static const std::string TogglePause;
    static const std::string EnsureWorkspaces;
    static const std::string CycleFocusMonitor;
    static const std::string CycleFocusWorkspace;
    static const std::string FocusMonitorNumber;
    static const std::string ReloadConfiguration;
    static const std::string WatchConfiguration;
    static const std::string Manage;
    static const std::string Unmanage;
    static const std::string MoveContainerToMonitorNumber;
    static const std::string MoveContainerToWorkspaceNumber;
    static const std::string MoveWorkspaceToMonitorNumber;
    static const std::string NewWorkspace;
    static const std::string SendContainerToMonitorNumber;
    static const std::string SendContainerToWorkspaceNumber;
    static const std::string WorkspaceName;
};
#ifdef __ADD_KOMOREBI_HEADER_IMPL__

const std::string KomorebiEvent::KomorebiConnect = "KomorebiConnect";
const std::string KomorebiEvent::KomorebiUpdate = "KomorebiUpdate";
const std::string KomorebiEvent::KomorebiDisconnect = "KomorebiDisconnect";
const std::string KomorebiEvent::FocusWorkspaceNumber = "FocusWorkspaceNumber";
const std::string KomorebiEvent::FocusMonitorWorkspaceNumber = "FocusMonitorWorkspaceNumber";
const std::string KomorebiEvent::FocusChange = "FocusChange";
const std::string KomorebiEvent::ChangeLayout = "ChangeLayout";
const std::string KomorebiEvent::ToggleTiling = "ToggleTiling";
const std::string KomorebiEvent::ToggleMonocle = "ToggleMonocle";
const std::string KomorebiEvent::ToggleMaximise = "ToggleMaximise";
const std::string KomorebiEvent::TogglePause = "TogglePause";
const std::string KomorebiEvent::EnsureWorkspaces = "EnsureWorkspaces";
const std::string KomorebiEvent::CycleFocusMonitor = "CycleFocusMonitor";
const std::string KomorebiEvent::CycleFocusWorkspace = "CycleFocusWorkspace";
const std::string KomorebiEvent::FocusMonitorNumber = "FocusMonitorNumber";
const std::string KomorebiEvent::ReloadConfiguration = "ReloadConfiguration";
const std::string KomorebiEvent::WatchConfiguration = "WatchConfiguration";
const std::string KomorebiEvent::Manage = "Manage";
const std::string KomorebiEvent::Unmanage = "Unmanage";
const std::string KomorebiEvent::MoveContainerToMonitorNumber = "MoveContainerToMonitorNumber";
const std::string KomorebiEvent::MoveContainerToWorkspaceNumber = "MoveContainerToWorkspaceNumber";
const std::string KomorebiEvent::MoveWorkspaceToMonitorNumber = "MoveWorkspaceToMonitorNumber";
const std::string KomorebiEvent::NewWorkspace = "NewWorkspace";
const std::string KomorebiEvent::SendContainerToMonitorNumber = "SendContainerToMonitorNumber";
const std::string KomorebiEvent::SendContainerToWorkspaceNumber = "SendContainerToWorkspaceNumber";
const std::string KomorebiEvent::WorkspaceName = "WorkspaceName";


#endif
