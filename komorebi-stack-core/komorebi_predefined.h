#pragma once
#include <string>
#include <Windows.h>
#define WM_KOMOREBI_EVENT (WM_USER+1)

// x is Json::Value type
#define String2HWND(x) (reinterpret_cast<HWND>((x).asUInt64()))


struct JsonKeyword {
    using string = std::string;
    //static const std::string 

    const static std::string Event;
    const static std::string State;

};
#ifdef __ADD_KOMOREBI_HEADER_IMPL__

const std::string JsonKeyword::Event = "event";
const std::string JsonKeyword::State = "state";


#endif

struct KomorebiState {

    const static std::string border_overflow_identifiers;
    const static std::string cross_monitor_move_behaviour;
    const static std::string float_identifiers;
    const static std::string has_pending_raise_op;
    const static std::string invisible_borders;
    const static std::string is_paused;
    const static std::string layered_whitelist;
    const static std::string manage_identifiers;
    const static std::string monitors;
    const static std::string mouse_follows_focus;
    const static std::string name_change_on_launch_identifiers;
    const static std::string new_window_behaviour;
    const static std::string resize_delta;
    const static std::string tray_and_multi_window_identifiers;

};

#ifdef __ADD_KOMOREBI_HEADER_IMPL__
const std::string KomorebiState::border_overflow_identifiers = "border_overflow_identifiers";
const std::string KomorebiState::cross_monitor_move_behaviour = "cross_monitor_move_behaviour";
const std::string KomorebiState::float_identifiers = "float_identifiers";
const std::string KomorebiState::has_pending_raise_op = "has_pending_raise_op";
const std::string KomorebiState::invisible_borders = "invisible_borders";
const std::string KomorebiState::is_paused = "invisible_borders";
const std::string KomorebiState::layered_whitelist = "layered_whitelist";
const std::string KomorebiState::manage_identifiers = "manage_identifiers";
const std::string KomorebiState::monitors = "monitors";
const std::string KomorebiState::mouse_follows_focus = "mouse_follows_focus";
const std::string KomorebiState::name_change_on_launch_identifiers = "name_change_on_launch_identifiers";
const std::string KomorebiState::new_window_behaviour = "new_window_behaviour";
const std::string KomorebiState::resize_delta = "resize_delta";
const std::string KomorebiState::tray_and_multi_window_identifiers = "tray_and_multi_window_identifiers";




#endif


struct KomorebiEvent {

    const static std::string KomorebiConnect;
    const static std::string KomorebiUpdate;
    const static std::string KomorebiDisconnect;
    const static std::string FocusWorkspaceNumber;
    const static std::string FocusMonitorWorkspaceNumber;
    const static std::string FocusChange;
    const static std::string ChangeLayout;
    const static std::string ToggleTiling;
    const static std::string ToggleMonocle;
    const static std::string ToggleMaximise;
    const static std::string TogglePause;
    const static std::string EnsureWorkspaces;
    const static std::string CycleFocusMonitor;
    const static std::string CycleFocusWorkspace;
    const static std::string FocusMonitorNumber;
    const static std::string ReloadConfiguration;
    const static std::string WatchConfiguration;
    const static std::string Manage;
    const static std::string Unmanage;
    const static std::string MoveContainerToMonitorNumber;
    const static std::string MoveContainerToWorkspaceNumber;
    const static std::string MoveWorkspaceToMonitorNumber;
    const static std::string NewWorkspace;
    const static std::string SendContainerToMonitorNumber;
    const static std::string SendContainerToWorkspaceNumber;
    const static std::string WorkspaceName;
    
    //stacking
    // for testing
    const static std::string StackWindow;
    const static std::string ResizeWindowEdge;
    const static std::string UnstackWindow;
    const static std::string CycleStack;


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

const std::string KomorebiEvent::StackWindow = "StackWindow";
const std::string KomorebiEvent::ResizeWindowEdge = "ResizeWindowEdge";
const std::string KomorebiEvent::UnstackWindow = "UnstackWindow";
const std::string KomorebiEvent::CycleStack = "CycleStack";



#endif
