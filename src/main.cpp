#include "include/raylib.h"
#include "generation.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <sstream>
using namespace std;

int roundToNearestMultiple(int number, int multiple) {
  return round(static_cast<double>(number) / multiple) * multiple;
}

// CheckCollisionRecs({camx, camy, (float)LoadTexture(image).width, (float)LoadTexture(image).height}, {(float)WIDTH / 2, (float)HEIGHT / 2, (float)LoadTexture(Player.startingPlayerImage).width, (float)LoadTexture(Player.startingPlayerImage).height}

void DrawOutlinedText(Font font,const char *text, int posX, int posY, int fontSize, Color color, int outlineSize, Color outlineColor) {
    DrawTextEx(font, text, {(float)posX - outlineSize, (float)posY - outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX + outlineSize, (float)posY - outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX - outlineSize, (float)posY + outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX + outlineSize, (float)posY + outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX, (float)posY}, fontSize, fontSize / 8, color);
}

class Player {
    public:
        Texture2D playerNorth;
        Texture2D playerSouth;
        Texture2D playerEast;
        Texture2D playerWest;
        Texture2D startingPlayerImage;
        Vector4 moveKeys;
        float moveSpeed;
        bool moving = false;
    public:
        void Unload() {
            UnloadTexture(playerNorth);
            UnloadTexture(playerSouth);
            UnloadTexture(playerEast);
            UnloadTexture(playerWest);
            UnloadTexture(startingPlayerImage);
        }
        void move(float& xToMove, float& yToMove) {
            if (IsKeyDown(moveKeys.x)) {
                startingPlayerImage = playerNorth;
                yToMove += moveSpeed;
                moving = true;
            }
            if (IsKeyDown(moveKeys.y)) {
                startingPlayerImage = playerWest;
                xToMove += moveSpeed;
                moving = true;
            }
            if (IsKeyDown(moveKeys.z)) {
                startingPlayerImage = playerSouth;
                yToMove -= moveSpeed;
                moving = true;
            }
            if (IsKeyDown(moveKeys.w)) {
                startingPlayerImage = playerEast;
                xToMove -= moveSpeed;
                moving = true;
            }
            if (!IsKeyDown(moveKeys.x) && !IsKeyDown(moveKeys.y) && !IsKeyDown(moveKeys.z) && !IsKeyDown(moveKeys.w)) {
                moving = false;
            }
        }
        void draw(int x, int y) {
            DrawTexture(startingPlayerImage, x, y, WHITE);
        }
} Player;

class HotBar {
    private:
        vector<vector<int>> items;
        int size;
        stringstream ss;
        Texture2D image = LoadTexture("images/slot.png");
        Texture2D rockImage = LoadTexture("images/rock.png");
        Texture2D selectedImage = LoadTexture("images/slot-selected.png");
        Font comic_sans = LoadFont("fonts/Comic Sans MS.ttf");
    public:
        HotBar(int size) : size(size) {
            items.resize(size, std::vector<int>(2, 0));
        }
        int selectedSlot = 0;

        void Unload() {
            UnloadTexture(image);
            UnloadTexture(selectedImage);
            UnloadTexture(rockImage);
            UnloadFont(comic_sans);
        }

        void add(int slot, int itemID, int amount) {
            if (slot >= 0 && slot < size) {
                if (amount == 0) {
                    TraceLog(LOG_WARNING, "If you add 0 items, it does nothing.");
                } else {
                    items[slot][0] = itemID;
                    items[slot][1] += amount;
                }
            } else {
                TraceLog(LOG_FATAL, "FATAL ERROR: stack overflow");
            }
        }
        void removeItemFromSlot(int slot, int amount) {
            if (slot >= 0 && slot < size) {
                if (amount == items[slot][1]) {
                    items[slot][0] = 0;
                }
                items[slot][1] -= amount;
            }
        }
        int getItemIDInSlot(int slot) {
            if (slot >= 0 && slot < size) {
                return items[slot][0];
            } else {
                TraceLog(LOG_FATAL, "FATAL ERROR: stack overflow");
                return 1;
            }
        }
        int getItemAmount(int slot) {
            if (slot >= 0 && slot < size) {
                return items[slot][1];
            } else {
                TraceLog(LOG_FATAL, "FATAL ERROR: stack overflow");
                return 1;
            }
        }
        void draw() {
            for (int i = 0; i < size; i++) {
                DrawTexture(image, image.width * i, 0, WHITE);
                if (getItemIDInSlot(i) == 1) {
                    DrawTexture(rockImage, image.width * i, 0, WHITE);
                    ss << getItemAmount(i);
                    DrawOutlinedText(comic_sans, ss.str().c_str(), image.width * i, 0, 20, WHITE, 1, BLACK);
                    ss.str(" ");
                    ss.clear();
                }
            }
            DrawTexture(selectedImage, selectedImage.width * selectedSlot, 0, WHITE);
            if (GetMouseWheelMove() != 0) {
                if (GetMouseWheelMove() < 0) {
                    selectedSlot++;
                    if (selectedSlot >= size) {
                        selectedSlot = 0;
                    }
                } else {
                    selectedSlot--;
                    if (selectedSlot < 0) {
                        selectedSlot = size - 1;
                    }
                }
            }
            if (getItemIDInSlot(selectedSlot) == 1) {
                DrawOutlinedText(comic_sans, "Rock", 5, 32, 20, WHITE, 1, BLACK);
            }
            if (getItemIDInSlot(selectedSlot) == 0) {
                DrawOutlinedText(comic_sans,"Items", 5, 32, 20, WHITE, 1, BLACK);
            }
        }
};

class Inventory {
    private:
        vector<vector<vector<int>>> items;
        stringstream ss;
        Texture2D image = LoadTexture("images/slot.png");
        Texture2D rockImage = LoadTexture("images/rock.png");
        Texture2D selectedImage = LoadTexture("images/slot-selected.png");
        Font comic_sans = LoadFont("fonts/Comic Sans MS.ttf");
    public:
        Inventory(int sizeX, int sizeY) : items(sizeX, vector<vector<int>>(sizeY, vector<int>(1, 0))) {}
        int selectedSlot = 0;

        void Unload() {
            UnloadTexture(image);
            UnloadTexture(selectedImage);
            UnloadTexture(rockImage);
        }

        void Init() {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 4; j++) {
                    items[i][j][1] = 0;
                }
            }
        }

        void add(int slotX, int slotY, int itemID, int amount) {
            if (amount == 0) {
                TraceLog(LOG_WARNING, "If you add 0 items, it does nothing.");
            } else {
                items[slotX][slotY][0] = itemID;
                items[slotX][slotY][1] += amount;
            }
        }
        void removeItemFromSlot(int slotX, int slotY, int amount) {
            if (amount == items[slotX][slotY][1]) {
                items[slotX][slotY][0] = 0;
            } else {
                items[slotX][slotY][1] -= amount;
            }
        }
        int getItemIDInSlot(int slotX, int slotY) {
            return items[slotX][slotY][0];
        }
        int getItemAmount(int slotX, int slotY) {
            return items[slotX][slotY][1];
        }
        void draw() {
            for (int i = 0; i < 5; i++) {
                DrawTexture(image, image.width * i, 50, WHITE);
                for (int j = 0; j < 4; j++) {
                    DrawTexture(image, image.width * i, image.height * j + 50, WHITE);
                    ss << getItemAmount(i, j);
                    if (getItemIDInSlot(i, j) == 1) {
                        DrawTexture(rockImage, image.width * i, image.height * j + 50, WHITE);
                    } 
                    if (getItemAmount(i, j) != 0)
                        DrawOutlinedText(comic_sans, ss.str().c_str(), image.width * i, image.height * j + 50, 20, WHITE, 1, BLACK);
                    ss.str(" ");
                    ss.clear();
                }
            }
        }
};

typedef struct Interactible {
    bool mined = false;
    Texture2D image;
    Texture2D selectedImage;
    int x, y;
    int health = 3;
    private:
        bool inffix = false;
        Texture2D break1 = LoadTexture("images/break1.png");
        Texture2D break2 = LoadTexture("images/break2.png");
    public:
    void draw(float& camx, float& camy, int WIDTH, int HEIGHT) {
        if (CheckCollisionPointRec(GetMousePosition(), {x + camx, y + camy, (float)image.width, (float)image.height}) && CheckCollisionCircleRec({(float)WIDTH / 2, (float)HEIGHT / 2}, 80, {x + camx, y + camy, (float)image.width, (float)image.height}) && mined == false) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                health -= 1;
            }
            DrawTexture(selectedImage, x + camx, y + camy, WHITE);
            if (health == 3) {
                inffix = false;
            }
            if (health == 2) {
                DrawTexture(break1, x + camx, y + camy - 10, WHITE);
            }
            if (health == 1) {
                DrawTexture(break2, x + camx, y + camy - 10, WHITE);
            }
            if (health == 0) {
                mined = true;
            }
        } else if (mined == false) {
            DrawTexture(image, x + camx, y + camy, WHITE);
            if (health == 2) {
                DrawTexture(break1, x + camx, y + camy - 10, WHITE);
            }
            if (health == 1) {
                DrawTexture(break2, x + camx, y + camy - 10, WHITE);
            }
            if (health == 0) {
                mined = true;
            }
        }
    }
    void collide(float& camx, float& camy, int WIDTH, int HEIGHT) {
        if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)image.width, (float)image.height}) && IsKeyDown(KEY_W) && mined == false) {
            camy -= Player.moveSpeed;
        }
        if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)image.width, (float)image.height}) && IsKeyDown(KEY_A) && mined == false) {
            camx -= Player.moveSpeed;
        }
        if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)image.width, (float)image.height}) && IsKeyDown(KEY_S) && mined == false) {
            camy += Player.moveSpeed;
        }
        if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)image.width, (float)image.height}) && IsKeyDown(KEY_D) && mined == false) {
            camx += Player.moveSpeed;
        }
    }
    bool Broken() {
        if (inffix == false && mined == true) {
            inffix = true;
            return true;
        } else {
            return false;
        }
    }
    void ReCreate() {
        health = 3;
        inffix = false;
        mined = false;
    }
    void Unload() {
        UnloadTexture(image);
        UnloadTexture(selectedImage);
        UnloadTexture(break1);
        UnloadTexture(break2);
    }
} Interactible;

void Input(float& camx, float& camy, bool& inventoryOpen, Inventory& inventory) {
    if (IsKeyPressed(KEY_F4)) {
        ToggleFullscreen();
    }
    if (IsKeyPressed(KEY_E)) {
        inventoryOpen = !inventoryOpen;
    }
    if (inventoryOpen == true) {
        inventory.draw();
    }
    Player.move(camx, camy);
}

int main() {
    const int WIDTH = 640;
    const int HEIGHT = 480;
    InitWindow(WIDTH, HEIGHT, "Curt, THE SNAIL, DESTROYER OF WORLDS!");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    InitAudioDevice();
    float camx = 0;
    float camy = 0;
    Interactible rock;
    Player.moveKeys = {KEY_W, KEY_A, KEY_S, KEY_D};
    Player.moveSpeed = 1;
    Player.playerNorth = LoadTexture("images/player-north.png");
    Player.playerSouth = LoadTexture("images/player-south.png");
    Player.playerEast = LoadTexture("images/player-east.png");
    Player.playerWest = LoadTexture("images/player-west.png");
    Player.startingPlayerImage = LoadTexture("images/player-east.png");
    rock.image = LoadTexture("images/rock.png");
    rock.selectedImage = LoadTexture("images/rock-selected.png");
    srand(time(0));
    rock.x = (rand() % (640 + 1) + 1);
    srand(time(0));
    rock.y = (rand() % (480 + 1) + 1);
    HotBar hotbar(5);
    bool first = true;
    Texture2D grass = LoadTexture("images/grass.png");
    bool invetoryOpen = false;
    Inventory inventory(5, 4);
    inventory.Init();
    Music Unknown = LoadMusicStream("songs/Unknown");
    Music closeToHome = LoadMusicStream("songs/closeToHome.mp3");
    PlayMusicStream(closeToHome);
    while (!WindowShouldClose()) {
        UpdateMusicStream(Unknown);
        UpdateMusicStream(closeToHome);
        BeginDrawing();
        drawWorld(grass, WIDTH, HEIGHT, camx, camy);
        Player.draw(WIDTH / 2, HEIGHT / 2);
        rock.draw(camx, camy, WIDTH, HEIGHT);
        rock.collide(camx, camy, WIDTH, HEIGHT);
        hotbar.draw();
        if (rock.Broken()) {
            hotbar.add(0, 1, 1);
            inventory.add(0, 0, 1, 1);
            srand(time(0));
            rock.x = (rand() % (640 + 1) + 1);
            srand(time(0));
            rock.y = (rand() % (480 + 1) + 1);
            rock.ReCreate();
        }
        Input(camx, camy, invetoryOpen, inventory);
        if (GetFPS() <= 100) {
            DrawFPS(0, 0);
        }
        ClearBackground(BLUE);
        EndDrawing();
    }
    Player.Unload();
    hotbar.Unload();
    rock.Unload();
    inventory.Unload();
    UnloadTexture(grass);
    UnloadMusicStream(Unknown);
    UnloadMusicStream(closeToHome);
    CloseWindow();
    return 0;
}

/* 1i_ii0>Set Inv Positionx positiony positionnot1CloneAsID0=translate00CloneAsIDInit Harvestedseti_ttoifthenelseifthenelsechange_SpriteCountbywhen I start as a clonei_ii0>Update Inv Blocksi_t-1>Drawi_t-1<Process and Draw ItemProcess Harvest List_NextSelID0=Draw Held.1_Modeletterofx=notChange Selection_NextSelID0set_NextSelIDtoifthenifthenelseifthenelseifthenelseifthenelsewhen I receiveanimateDo Suckxywait0=timerwait>Steve_sxof0=notandor0Get InvID for Tileccountix0>xabsofyabsof+refIdx_t2<xabsof0.25<yabsof0.9<andix2*1-itemof_Invc=notix2*1-cix_HeldInvID=ixset_NextSelIDtoifthenreplace itemof_Invwithix2*countix2*itemof_Inv+ix2*itemof_InvmaxStack>notmaxStack0<orupdate inventory-1delete this clonechange_SpriteCountbybroadcastix2*itemof_InvmaxStack-ix2*maxStackreplace itemof_Invwithsetcounttoifthenelsereplace itemof_InvwithifthenStuckIn0=xrefIdx_t/0.2*yrefIdx_t/0.2*0.04changesybysetsytosetsxtoifthenifthenifthensetrefIdx_ttoifthensetwaittoifthendefineProcess and Draw Item_Mode =_ModeS=ory_ScrY-40*StuckIn0=c132=notand4200CloneAsID_TimeReal+*sinof*changet_ilumTmpbydrawOrHidex_ScrX-40*flooroft_ilumTmpfloorofifthensett_ilumTmptoshow1=0setshowtohideifthen_ticks_MaxHarvestCloneAsID<StuckIn0<or-1delete this clonechange_SpriteCountbyc132=Do Arrow In FlightStuckIn0=sxIsBlock_txy0.4-refIdx_t0>0sx-sxchangexbysetsxtot_tileIdxitemof_LevelrefIdx_t_DMUL*14+itemof_BLOCK_DATA0>-1delete this clonechange_SpriteCountbyrefIdx_t_DMUL*7+itemof_BLOCK_DATArefIdx_tD=refIdx_t.=ort_tileIdx1-itemof_LevelrefIdx_t_DMUL*7+itemof_BLOCK_DATArefIdx_tL=nott_tileIdx1+itemof_LevelrefIdx_t_DMUL*7+itemof_BLOCK_DATArefIdx_tR=notNsetrefIdx_ttoifthensetrefIdx_ttosetrefIdx_ttoifthensetrefIdx_ttosetrefIdx_ttorefIdx_tL=-0.1setsxtorefIdx_tR=0.1setsxtoifthen-0.03sy-0.6<-0.6setsytosyIsBlock_txy0.4-refIdx_t0>sy0<y0.4-floorof1.41+0sx0.5*setsxtosetsytosetytosx0.5*setsxtoIsBlock_txy0.4-refIdx_t0>1changeybyifthenifthenelseifthenchangeybyifthenchangesybyifthenelseifthensetrefIdx_ttoifthensetrefIdx_ttoifthenchangexbyStuckInitemof_LevelrefIdx_t_DMUL*3+itemof_BLOCK_DATAY=not0setStuckIntoifthensetrefIdx_tto_Health_s0>Do Suck_xx-_yy-ifthenifthenelseifthenelseifthenGet Illuminationyfloorof_lsx*xfloorof+1+_Lighting?1=lightlightMod=notlightModlight1+itemof_Gammasetbrightnesseffect tosetlighttoifthenlightModlight0=show1=0setshowtohideifthenifthensetlighttoifthenelserepeatifthenelsedefineDo Active Block2020i_titemof_LevelRefrefIdx_t =stopthis scriptfrefIdx_t1+itemof_RefData=40refIdx_t2+itemof_RefData*changeiybyifthenifthensetrefIdx_ttosetiytosetixtodefineGet InvID for Tiletilecount1Get Stack Limittile36tileix2*1-itemof_Inv=maxStack0<ix2*itemof_Inv0=stopthis scriptifthenix2*itemof_InvmaxStack<stopthis scriptifthenifthenelse1changeixbyifthen1360ix2*itemof_Inv=stopthis script1changeixbyifthen0setixtorepeatsetixtorepeatsetixtodefineUpdate Inv BlocksStuckIn0=_Mode =_ModeS=orStuckIn9>andor_ToolTipIDi_ii=0 thinkset_ToolTipIDtoshow1=0setshowtohide#setctoiftheniftheni_ii64=StuckIn2*0-itemof_Inv0>andSet Inv Positionmouse xmouse y86cStuckIn2*1-itemof_Inv=notStuckIn2*1-itemof_Invc#=show1=0setshowtohideifthenc_DMUL*17+itemof_BLOCK_DATAshow0=1setshowtoshowifthenswitch costume toifthenelsesetctoi_ii64<c#=notmouse down?notmouse xx position-absof18<mouse yy position-absof18<andandand_ToolTipIDi_ii=_ToolTipWait15<_tickschange_ToolTipWaitby_ToolTipWait100<c_DMUL*2+itemof_BLOCK_DATA100set_ToolTipWaittothinkifthenifthenelse_ToolTipID0=i_ii0set_ToolTipWaittoset_ToolTipIDtoifthenifthenelse_ToolTipIDi_ii=0 thinkset_ToolTipIDtoifthenifthenelseifthenifthenifthenifthenelsedefinei_ii0>go tofrontlayerifthenwhen I receiveswitch modeDraw HeldchangeToi_t-1=changeTo.=notchangeTo99999_HeldC_DMUL*10+itemof_BLOCK_DATA1=_LastDir-90=_HeldC_DMUL*16+itemof_BLOCK_DATAswitch costume to_HeldC_DMUL*17+itemof_BLOCK_DATAswitch costume to65set size to%ifthenelse_HeldC_DMUL*17+itemof_BLOCK_DATA40set size to%switch costume to-1arm to frontbroadcastgo tofrontlayersetlighttoifthenelsesetiytoset_HeldCto_HeldC#=_Mode =notorshow1=0setshowtohideifthenshow0=1setshowtoshow_HeldC130=_ArmFrame4*Steve Armdirectionof018ixsinof*+1418ixcosof*+180CursorBowPullofceilingof_HeldC_DMUL*17+itemof_BLOCK_DATA+switch costume tochangeixbysetytosetxtosetixtosetrefIdx_tto_ArmFrame4*Steve Armdirectionof023ix_LastDir0.28*-sinof*+1423ix_LastDir0.28*-cosof*+_LastDir90-_HeldC_DMUL*10+itemof_BLOCK_DATA1=_LastDir-90=Set Costume to_HeldC_DMUL*17+itemof_BLOCK_DATASet Costume to_HeldC_DMUL*16+itemof_BLOCK_DATAifthenelseifthenchangeixbysetytosetxtosetixtosetrefIdx_tto_x_ScrX-40*floorofx+_y_ScrY-40*floorofy+ixiy=notix_HeldC_DMUL*10+itemof_BLOCK_DATA1=-45changeixbyixpoint in directionifthensetiyto_SteveLightlight=not_Lighting?1=and_SteveLightlight1+itemof_Gammasetbrightnesseffect tosetlighttoifthenifthengo to x:y:ifthenelseifthenifthenelseifthenifthendefineInit Inventory Items#0-160-1589065064064myself-1changei_iibycreate clone of0seti_iitorepeatsetStuckIntoseti_iitogo tofrontlayerhidesetshowtoset size to%clear graphic effectspoint in directiongo to x:y:setcounttosetctodefineGet Stack Limittiletile_DMUL*18+itemof_BLOCK_DATAmaxStack0>0maxStack-setmaxStacktotile_DMUL*10+itemof_BLOCK_DATAmaxStack1=maxStack8=or1setmaxStackto64setmaxStacktoifthenelsesetmaxStacktoifthenelsesetmaxStacktodefineDo Arrow In Flightsx-0.04sy-0.4<-0.4setsytosyAngle Arrowdirection45-IsBlock_tx0.1maxStacksinof*+y0.1maxStackcosof*+refIdx_t0>0.1maxStacksinof*0.1maxStackcosof*t_tileIdxrefIdx_t0=sx-0.5*sy-0.5*IsBlock_txsx+ysy+changeybychangexby13100setsytosetsxtosetctorepeat untilsetStuckIntosetsytosetsxto1maxStacklength of_Mob>maxStackitemof_MobStuckIn0>maxStack2+itemof_Mobt_tileIdx=StuckIn99>StuckIn102=notandmaxStack2+itemof_Mob_lsx+t_tileIdx=andormaxStack9+9sxsx*sysy*+sqrtof*ceilingof-1-1stopthis scriptsetStuckIntochange_SpriteCountbyreplace itemof_Mobwithifthen_MobMulchangemaxStackbyifthensetStuckInto0x_x-absof0.5<y_y-absof0.9<and-9sxsx*sysy*+sqrtof*ceilingof_DefenseMul*floorofupdate health-1-1stopthis scriptsetStuckIntochange_SpriteCountbybroadcastchange_Health_sbyifthensetStuckIntorepeat untilsetmaxStacktoifthenelsesetmaxStacktochangeybyifthenchangesybychangexbydefineAngle Arrowsx0=sy0>90setmaxStackto-90setmaxStacktoifthenelsesysx/atanofsx0<sy0>180changemaxStackbysy0<-180changemaxStackby90setmaxStacktoifthenelseifthenelseifthensetmaxStackto135maxStack-point in directionifthenelsedefineProcess Harvest List2_ClearHarvestIdx5+length of_Harvest<_ClearHarvestIdx1+itemof_Harvest_ClearHarvestIdx2+itemof_Harvesty0=x1-_lsx/floorof0.5+x1-_lsxmod0.5+setxtosetyto_ClearHarvestIdx3+itemof_Harvest_ClearHarvestIdx4+itemof_Harvest_ClearHarvestIdx5+itemof_Harvestsxabsof0.15>timer2+setwaittotimer0.2+setwaitto_ClearHarvestIdx6+itemof_Harvestsy-999=0.050.1pick randomtosetsyto-1-115show1=0setshowtohidemyselfDraw Held.6change_ClearHarvestIdxbycreate clone ofifthenchangelightbychange_MaxHarvestbychangeCloneAsIDbyifthensetsytoifthenelsesetsxtosetcounttosetctoifthensetytosetxtoifthenrepeatdefinei_ii0=stopthis script_Modec=259setoffset_iito_Modef=517setoffset_iito_Modech=775setoffset_iito_Modex=1033setoffset_iito_Modexi=1291setoffset_iito1setoffset_iitoifthenelseifthenelseifthenelseifthenelseSet Inv Positionoffset_iii_ii4*1-+itemof_GUI_posoffset_iii_ii4*0-+itemof_GUI_posnotoffset_iii_ii4*2-+itemof_GUI_posifthenelseifthenwhen I receiverearrange guiIsBlock_txyyfloorof_lsx*xfloorof+1+t_tileIdxitemof_LevelrefIdx_t_DMUL*3+itemof_BLOCK_DATAY=1setrefIdx_tto0setrefIdx_ttoifthenelsesetrefIdx_ttosett_tileIdxtodefinei_t-1=0.5go tofrontlayerwaitsecondsifthenwhen I receivegoDrawx_ScrX--7<translate_ScrXx-6+13/floorof13*0x_ScrX-6<nottranslatex_ScrX-7+13/floorof-13*0iftheny_ScrY--5.5<translate0_ScrYy-4.5+10/floorof10*y_ScrY-4.5<nottranslate0y_ScrY-5.5+10/floorof-10*ifthenDo Active BlockSwitch CostumeDrawOrHideTilex_ScrX-40*ix+floorofy_ScrY-40*iy+floorofcostumenumberifthenelseifthenelsedefinei_ii1<i_t-1<delete this cloneifthenifthenwhen I receivepost chunk load00Init Inventory Itemsrearrange guiinit0100Draw Held#-1set_NextSelIDtosetStuckIntoset_ClearHarvestIdxtoset_HeldInvIDtoseti_iitobroadcastand waitset_ToolTipIDtosetshowtohidewhen I receiveinit1bChange SelectiongroupIDinitOnlygroupIDabsofinitOnlynotDraw Held2_HeldInvID*1-itemof_Invchange of toolbroadcastifthenset_HeldInvIDtodefineGet Illuminationidx_XRAY0=idxitemof_Light_GLight-idxlength of_Level+itemof_LightlightModt_ilumTmp<t_ilumTmpsetlightModtoifthensetlightModtosett_ilumTmpto15setlightModtoifthenelsedefine-1_Lighting?1=clear graphic effectsifthenelsesetlighttowhen I receivelighting mode change@@Register Tile Deletion betweenandfromIDtoID_DMULi_tlength of_BLOCK_DATA>i_t16+itemof_BLOCK_DATAoffset_iitoID>fromIDtoID-1-i_t16+offset_iireplace itemof_BLOCK_DATAwithchangeoffset_iibyoffset_iifromID<noti_t16+-99999replace itemof_BLOCK_DATAwithiftheni_t17+itemof_BLOCK_DATAoffset_iitoID>fromIDtoID-1-i_t17+offset_iireplace itemof_BLOCK_DATAwithchangeoffset_iibyoffset_iifromID<noti_t17+-99999replace itemof_BLOCK_DATAwithifthen_DMULchangei_tbyifthenelsesetoffset_iitoifthenelsesetoffset_iitorepeat untilseti_ttodefineDrawOrHideTilepxpycostumec-1>BIGpxpycostumeStuckIn0=show0=1setshowtoshowifthenshow1=0setshowtohideifthenifthenelseswitch costume togo to x:y:switch costume toifthendefineInit Harvested-290c_DMUL*17+itemof_BLOCK_DATA40set size to%clear graphic effectsswitch costume topoint in directionseti_ttodefineSet Inv Positionxyinternal?invIDinternal?xysetytosetxtoinvIDi_ii3*2-invIDi_ii3*1-xi_ii3*0-yx-999>xyc#=show1=0setshowtohideifthenshow0=1setshowtoshowifthenifthenelsego to x:y:#show1=0setshowtohideifthensetctoifthenelsereplace itemof_InvPoswithreplace itemof_InvPoswithreplace itemof_InvPoswithsetStuckIntoifthendefineSet Costume tocotume #costumenumbercotume #=notcotume #switch costume toifthendefineReally Delete? (y/n)answery=@@Register Tile Deletion betweenand2428ifthenaskand waitgrasshideswitch costume toclear graphic effectswhen I receivegreen flaginit0500pick randomto-360360pick randomto1000_ScrXfloorof7-_ScrYfloorof5-xy_lsx*+1+-1160setCloneAsIDto1013myself101500pick randomto1100pick randomto-360360pick randomtopoint in directionsetcoloreffect toset size to%11changei_tbychangexbyrepeatcreate clone of-13_lsx13-1changeybychangei_tbychangexbyrepeat#-1-1go tofrontlayersetCloneAsIDtoseti_ttoset_HeldCtorepeatsetlighttosetctoseti_ttosetytosetxtogobackwardlayerspoint in directionset size to%clear graphic effectsdefinedrawOrHidepxpypxpypxx position=pyy position=andshow0=1setshowtoshowifthenshow1=0setshowtohideifthenifthenelsego to x:y:define-100001000000000pick randomtotranslatetxtydefine0setshowtohidetxchangexbyxroundsetxtotychangeyby101500pick randomto1100pick randomto-360360pick randomtopoint in directionsetcoloreffect toset size to%repeaty0<1seti_ttoy_lsy<notx0<x_lsx<notororlength of_Levelseti_ttoy_lsx*x+1+seti_ttoifthenelsei_titemof_Levelcountc=not-1setctoifthensetcounttoifthenelseSwitch CostumeforceLightdefine101500pick randomto1100pick randomto-360360pick randomtopoint in directionsetcoloreffect toset size to%repeatthrottle0>ifthenGet Illuminationi_t0lightMod0=40lightsetlightModtosetcounttoi_titemof_Levelcount1=lightMod14>_Lighting?0=orandlightc1setStuckIntosetcounttosetlightModtoifthensetcounttolightModlight=notcountc=notforceLight11_LightProbpick randomto=ororand1lightMod_Lighting?1=light1+itemof_Gammasetbrightnesseffect to-1setctoifthenelsesetlighttochange_LightProbbyStuckIn0=countc=notandcountc_DMUL*16+itemof_BLOCK_DATAcountcostumenumber=notcountc1=1000gobackwardlayers-1changethrottlebyifthenswitch costume toifthensetcounttosetctoifthenifthenifthenelsesetStuckIntowhen I start as a clone10repeat1500pick randomto1100pick randomto-360360pick randomtopoint in directionsetcoloreffect toset size to% */