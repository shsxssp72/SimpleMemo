//
// Created by 星落_月残 on 2019/1/22.
//

#ifndef SIMPLEMEMO_CONSTANTS_H
#define SIMPLEMEMO_CONSTANTS_H
#pragma once

#include <string>
#include <climits>

const std::string DEFAULT_MEMO_FILE_NAME="Memo.xml";
const std::string UI_LOAD_LISTENER_NAME="onLoadMemo";
const std::string UI_SAVE_LISTENER_NAME="onSaveMemo";
const std::string MAINCONTROLLER_LOAD_HANDLER_NAME="onLoadMemo_MainController";
const std::string MAINCONTROLLER_SAVE_HANDLER_NAME="onSaveMemo_MainController";
const std::string MEMOCORE_LOAD_HANDLER_NAME="onLoadMemo_Core";
const std::string MEMOCORE_SAVE_HANDLER_NAME="onSaveMemo_Core";

constexpr int COMPARER_IGNORE_PRIORITY=-1;
constexpr int COMPARER_HIGHEST_PRIORITY=0;
constexpr int COMPARER_FIRST_PRIORITY=1;
constexpr int COMPARER_SECOND_PRIORITY=2;
constexpr int COMPARER_THIRD_PRIORITY=3;
constexpr int COMPARER_FOURTH_PRIORITY=4;
constexpr int COMPARER_FIFTH_PRIORITY=5;
constexpr int COMPARER_SIXTH_PRIORITY=6;
constexpr int COMPARER_SEVENTH_PRIORITY=7;
constexpr int COMPARER_LOWEST_PRIORITY=INT_MAX;

const std::string DEFAULT_STATE_LISTENER_NAME="onActivation";
const std::string DEFAULT_INITIAL_STATE_NAME="InitialState";
const std::string EDIT_STATE_NAME="EditState";
const std::string NEW_STATE_NAME="NewState";
const std::string DISPLAY_STATE_NAME="DisplayState";
const std::string NEWSAVE_STATE_NAME="NewSaveState";
const std::string EDITSAVE_STATE_NAME="EditSaveState";
const std::string EDITCANCEL_STATE_NAME="EditCancelState";

const std::string INITIAL_STATE_HANDLER_NAME="InitialStateHandler";
const std::string EDIT_STATE_HANDLER_NAME="EditStateHandler";
const std::string NEW_STATE_HANDLER_NAME="NewStateHandler";
const std::string DISPLAY_STATE_HANDLER_NAME="DisplayStateHandler";
const std::string NEWSAVE_STATE_HANDLER_NAME="NewSaveStateHandler";
const std::string EDITSAVE_STATE_HANDLER_NAME="EditSaveStateHandler";
const std::string EDITCANCEL_STATE_HANDLER_NAME="EditCancelStateHandler";


#endif //SIMPLEMEMO_CONSTANTS_H
