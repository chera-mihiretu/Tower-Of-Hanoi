#include "Main_Menu.h"

Main_Menu::Main_Menu(int x_start, int x, int y) :
    width(x),
    height(y),
    start(x_start),
    timer(0),
    showDial( "Help", my_home::howToPlay), 
    restart("You Sure, Wanna Restart", true),
    gameOverD("You Win. Replay ?", true)
{
    resetTime();
    onRestart = false;
    onDialog = false;
    rest = false;
}

void Main_Menu::restartGame()
{
    rest = true;
    resetTime();
}

void Main_Menu::DrawIcons()
{
    if (timer == 0) {
        timer = GetTime() + 1;
    }
    else if (timer < GetTime()) {
        timer += 1;
        add_second();
    }

    DrawText(callTo().c_str(), start + width / 2 - MeasureText(callTo().c_str(), 20) / 2, height / 4 - 40, 20, BLACK);
    
   
    fit::DrawBoarder({(float) start + (width / 2 - (MeasureText("Restart", 30) / 2)),(float)height / 4 }, { (float)MeasureText("Restart", 30), 30 }, 5, GREEN);
    DrawText("Restart", start + width / 2-(MeasureText("Restart", 20) / 2), height / 4+5, 20, BLACK);
    fit::DrawBoarder({ (float)start + (width / 2 - (MeasureText("Help ?", 30) / 2)),(float)height / 4 + 40} , { (float)MeasureText("Help ?", 30), 30 }, 5, GREEN);
    DrawText("Help ?", start + width / 2 - (MeasureText("Help ?", 20) / 2), height / 4 + 45, 20, BLACK);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (handleClick((int)GetTouchX(), (int)GetTouchY()) == 0) { // restart is clicked
            if(!onDialog)
                onRestart = true;
            
        }
        else if (handleClick((int)GetTouchX(), (int)GetTouchY()) == 1) { // help is clicked
            if(!onRestart)
                onDialog = true;
        }
    }

    if (IsKeyPressed(KEY_R)) {
        if (!onDialog)
            onRestart = true;
    }
    else if (IsKeyPressed(KEY_H)) {
        if (!onRestart)
            onDialog = true;
    }

    if (onDialog) {
        showDial.DrawTheDialog();
        showDial.Draw();
        if (showDial.response() == -1) {
            onDialog = false;
            showDial.reset();
        }
    }
    if (onRestart) {
        restart.DrawTheDialog();
        restart.Draw();
        if (restart.response() == 1) {
            restartGame();
            onRestart = false;
            restart.reset();
        }
        else if (restart.response() == 0) {
            onRestart = false;
            restart.reset();
        }
    }
}

void Main_Menu::setDiskNo(int value)
{
    diskNo = value;
}

int Main_Menu::getDiskNo()
{
    return diskNo;
}

void Main_Menu::resetTime()
{
    for (int& x : playedTime) {
        x = 0;
    }
}

void Main_Menu::add_second()
{
    
    if (playedTime[0] >= 59) {
        playedTime[0] = 0;
        if (playedTime[1] >= 59) {
            if (playedTime[2] >= 11)
                playedTime[0] = playedTime[1] = playedTime[2] = 0;
            playedTime[2] += 1;
            playedTime[1] = 0;
        }
        else {
            playedTime[1] += 1;
        }
        
    }
    else {
        playedTime[0] += 1;
    }
}

std::string Main_Menu::toString(int num)
{
    std::string t;
    std::stringstream* convert = new std::stringstream();
    *convert << num;
    *convert >> t;

    
    return t;
}

std::string Main_Menu::callTo()
{
    return toString(playedTime[2]) + ":" + toString(playedTime[1]) + ":" + toString(playedTime[0]);
}

int Main_Menu::handleClick(int x, int y)
{
    if (x > start + (width / 2 - (MeasureText("Restart", 30) / 2)) && x < (start + (width / 2 - (MeasureText("Restart", 30) / 2))+(MeasureText("Restart", 30)))) {
        if (y > height / 4 && y < (height / 4+30)) {
            return 0;
        }
    }
    if (x > start + (width / 2 - (MeasureText("Help ?", 30) / 2)) && x < (start + (width / 2 - (MeasureText("Help ?", 30) / 2)) + (MeasureText("Help ?", 30)))) {
        if (y > height / 4 + 40 && y < (height / 4 + 70)) {
            return 1;
        }
    }
}

bool Main_Menu::restartClicked()
{
    return rest;
}


void Main_Menu::drawDiskSelector()
{

    for (int i = 0; i < 3; i++) {
        if (i == 1) {
            DrawText(toString(getDiskNo()).c_str(), start + (width / 2), height / 2, 30, BLACK);
            fit::DrawBoarder(Vector < float > {(float) start + (width / 2) -25, (float)height / 2 - 3},
                Vector<float>{ 60,36 }, 1, BROWN);
        }
        else {
            DrawText(i == 0 ? "<" : ">", start + (width / 2) - (1 - i) * 40, height / 2, 30,BLACK);
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int x = GetTouchX(), y = GetTouchY();
        if (x > start + (width / 2) - 40 && x < start + (width / 2)-40+MeasureText("<", 30)) {
            if (y > height / 2 && y < height / 2 + 40) {
                if (diskNo > 3)
                    setDiskNo(diskNo - 1);
            }
        }
        if (x > start + (width / 2) + 40 && x < start + (width / 2) + 40 + MeasureText(">", 30)) {
            if (y > height / 2 && y < height / 2 + 40) {
                if (diskNo < 7)
                    setDiskNo(diskNo + 1);
            }
        }
    }
    if (IsKeyPressed(KEY_LEFT)) {
        if (diskNo > 3)
            setDiskNo(diskNo - 1);
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        if (diskNo < 7)
            setDiskNo(diskNo + 1);
    }
}

int Main_Menu::gameOver()
{
    gameOverD.DrawTheDialog();
    gameOverD.Draw();
    gameOverD.setDetail(callTo());
    if (gameOverD.response() == 0) {
        return 0;
    }
    else if (gameOverD.response() == 1)
    {
        return 1;
    }
    return -1;
}