#include "main.h"
#include <imgui_internal.h>
#include <dwmapi.h>

HWND hwnd;
RECT rc;

void move_window() {

    ImGui::SetCursorPos(ImVec2(0, 0));
    if (ImGui::InvisibleButton("##invisible window", ImVec2(WIDTH, HEIGHT)));

    if (ImGui::IsItemActive()) {

        GetWindowRect(hwnd, &rc);
        MoveWindow(hwnd, rc.left + ImGui::GetMouseDragDelta().x, rc.top + ImGui::GetMouseDragDelta().y, WIDTH, HEIGHT, TRUE);

    }

}

void RenderBlur(HWND hwnd)
{
    struct ACCENTPOLICY
    {
        int na;
        int nf;
        int nc;
        int nA;
    };
    struct WINCOMPATTRDATA
    {
        int na;
        PVOID pd;
        ULONG ul;
    };

    const HINSTANCE hm = LoadLibrary(L"user32.dll");
    if (hm)
    {
        typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

        const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, "SetWindowCompositionAttribute");
        if (SetWindowCompositionAttribute)
        {
            ACCENTPOLICY policy = { 3, 0, 0, 0 }; // and even works 4,0,155,0 (Acrylic blur)
            WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
            SetWindowCompositionAttribute(hwnd, &data);
        }
        FreeLibrary(hm);
    }
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    WNDCLASSEXW wc;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = nullptr;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = L"ImGui";
    wc.lpszClassName = L"Example";
    wc.hIconSm = LoadIcon(0, IDI_APPLICATION);

    RegisterClassExW(&wc);
    hwnd = CreateWindowExW(NULL, wc.lpszClassName, L"Example", WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (WIDTH / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (HEIGHT / 2), WIDTH, HEIGHT, 0, 0, 0, 0);
    RenderBlur(hwnd);

    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    POINT mouse;
    rc = { 0 };
    GetWindowRect(hwnd, &rc);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.Fonts->AddFontFromMemoryTTF(&ubuntu_1, sizeof ubuntu_1, 15, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ico_0 = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 21, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ico_1 = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 28, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ubu_0 = io.Fonts->AddFontFromMemoryTTF(&ubuntu_0, sizeof ubuntu_0, 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ubu_1 = io.Fonts->AddFontFromMemoryTTF(&ubuntu_0, sizeof ubuntu_0, 25, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ubu_2 = io.Fonts->AddFontFromMemoryTTF(&ubuntu_2, sizeof ubuntu_2, 25, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ubu_child = io.Fonts->AddFontFromMemoryTTF(&ubuntu_1, sizeof ubuntu_1, 15, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);

    ImGui::SetNextWindowPos(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2 - WIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - HEIGHT / 2));

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {

            ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT));
            ImGui::SetNextWindowPos(ImVec2(0, 0));

            CustomStyleColor();
            D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
          //  if (bg == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, background, sizeof(background), &info, pump, &bg, 0);
            if (lg == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo, sizeof(logo), &info, pump, &lg, 0);

           // ImGui::GetBackgroundDrawList()->AddImage(bg, ImVec2(0, 0), ImVec2(1920, 1080), ImVec2(0, 0), ImVec2(1, 1), ImColor(150, 150, 150, 255));

            static bool menu = true;
            ImGui::Begin("Hello, world!", &menu, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
            {

                const auto& p = ImGui::GetWindowPos();
                ImGuiStyle* s = &ImGui::GetStyle();


                const int vtx_idx_1 = ImGui::GetWindowDrawList()->VtxBuffer.Size;
                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(192 + p.x, 0 + p.y), ImVec2(WIDTH + p.x, HEIGHT + p.y), ImColor(32, 31, 37, 255), s->WindowRounding, ImDrawFlags_RoundCornersRight);
                ImGui::ShadeVertsLinearColorGradientKeepAlpha(ImGui::GetWindowDrawList(), vtx_idx_1, ImGui::GetWindowDrawList()->VtxBuffer.Size, ImVec2(169 + p.x, 0 + p.y), ImVec2(WIDTH + p.x, HEIGHT + p.y), ImColor(32, 31, 37, 255), ImColor(18, 17, 22, 255));

                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(192 + p.x, HEIGHT + p.y), ImColor(35, 32, 45, 200), s->WindowRounding, ImDrawFlags_RoundCornersLeft);
                ImGui::GetWindowDrawList()->AddRect(ImVec2(0 + p.x, 0 + p.y), ImVec2(WIDTH + p.x, HEIGHT + p.y), ImColor(39, 38, 45, 255), s->WindowRounding, ImDrawFlags_None, 1.5f);
                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(192 + p.x, 0 + p.y), ImVec2(193.5f + p.x, HEIGHT + p.y), ImColor(39, 38, 45, 255), 0);

                ImGui::GetWindowDrawList()->AddLine(ImVec2(45 + p.x, 54 + p.y), ImVec2(192 + p.x, 54 + p.y), ImColor(29, 34, 53, 255), 0);
                ImGui::GetWindowDrawList()->AddLine(ImVec2(192 + p.x, 100 + p.y), ImVec2(WIDTH + p.x, 100 + p.y), ImColor(38, 37, 43, 255), 0);

                ///////////////////////////////////////////// LOGO + NAME AND DATA

                ImGui::GetWindowDrawList()->AddText(ubu_child, 15, ImVec2(686 + p.x, 31 + p.y), ImColor(225, 225, 230, 255), "Fuji");
                ImGui::GetWindowDrawList()->AddImage(lg, ImVec2(735 + p.x, 21 + p.y), ImVec2(770 + p.x, 56 + p.y), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255));
                ImGui::GetWindowDrawList()->AddText(ImVec2(683 + p.x, 66 + p.y), ImColor(65, 64, 69, 255), "DEC 11, 13:32");

                ///////////////////////////////////////////// CHEAT NAME

                ImGui::GetWindowDrawList()->AddText(ubu_1, 25, ImVec2(45 + p.x, 20 + p.y), ImColor(255, 255, 255, 255), "Sapphire");

                ImGui::SetCursorPosY(73);

                ///////////////////////////////////////////// TABS

                ImGui::BeginGroup();
                {
                    ImGui::TextColored(ImColor(77, 80, 97, 255), "\t  RAGEBOT");

                    if (ImGui::Tab("A", "General", tabs == 0, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 0;

                    if (ImGui::Tab("B", "Anti-Aim", tabs == 1, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 1;

                    ImGui::TextColored(ImColor(77, 80, 97, 255), "\t  LEGITBOT");

                    if (ImGui::Tab("D", "Triggerbot", tabs == 3, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 3;

                    if (ImGui::Tab("C", "General ", tabs == 4, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 4;

                    if (ImGui::Tab("E", "More ", tabs == 5, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 5;

                    ImGui::TextColored(ImColor(77, 80, 97, 255), "\t  VISUALS");

                    if (ImGui::Tab("F", "Players", tabs == 6, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 6;

                    if (ImGui::Tab("C", "World", tabs == 7, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 7;

                    if (ImGui::Tab("E", "More", tabs == 8, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 8;

                    ImGui::TextColored(ImColor(77, 80, 97, 255), "\t  OTHER");

                    if (ImGui::Tab("G", "Misc", tabs == 9, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 9;

                    if (ImGui::Tab("H", "Skins", tabs == 10, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 10;

                    if (ImGui::Tab("I", "Configs", tabs == 11, ImVec2(200, 25), true, ImGuiButtonFlags_None)) tabs = 11;

                }
                ImGui::EndGroup();

                tab_alpha = ImClamp(tab_alpha + (4.f * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);
                if (tab_alpha == 0.f && tab_add == 0.f) active_tab = tabs;

                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * s->Alpha);

                ImGui::SetCursorPos(ImVec2(210, 60));

                ///////////////////////////////////////////// SUB_TABS

                ImGui::BeginGroup();
                {
                    if (active_tab == 0) {
                        if (ImGui::Tab("", "Enemy", sub_tabs == 0, ImVec2(70, 25), false, ImGuiButtonFlags_None)) sub_tabs = 0;

                        if (ImGui::Tab("", "Team", sub_tabs == 1, ImVec2(70, 25), false, ImGuiButtonFlags_None)) sub_tabs = 1;

                        if (ImGui::Tab("", "Other", sub_tabs == 2, ImVec2(70, 25), false, ImGuiButtonFlags_None)) sub_tabs = 2;
                    }
                }
                ImGui::EndGroup();

                subtab_alpha = ImClamp(subtab_alpha + (4.f * ImGui::GetIO().DeltaTime * (sub_tabs == active_subtab ? 1.f : -1.f)), 0.f, 1.f);
                if (subtab_alpha == 0.f && subtab_add == 0.f) active_subtab = sub_tabs;

                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, subtab_alpha * s->Alpha);

                ImGui::SetCursorPos(ImVec2(213, 122));

                ImGui::BeginChild("General-CHILD", ImVec2(566, 445), true, ImGuiWindowFlags_NoBackground);
                {


                    if (active_tab == 0 && active_subtab == 0) {

                        ImGui::BeginGroup(); // START GROUP
                        {
                            ImGui::BeginChildPos("GENERAL", ImVec2(267, 310));
                            {

                                ImGui::Checkbox("Checkbox", &check_0);

                                ImGui::SliderInt("Slider Integer", &slider_one, 1, 100, "%d%%");

                                ImGui::InputTextWithHint("Textfield", "@Des1derata", input, 64);

                                ImGui::Combo("Combobox", &selectedItem, items, IM_ARRAYSIZE(items), 5);

                            }
                            ImGui::EndChildPos();


                            ImGui::BeginChildPos("MISC", ImVec2(267, 110));
                            {

                                if (ImGui::Button("Button", ImVec2(227, 37)));

                            }
                            ImGui::EndChildPos();


                            ImGui::BeginChildPos("OTHER", ImVec2(267, 260));
                            {

                                ImGui::Checkbox("Checkbox one", &check_1);

                                ImGui::Checkbox("Checkbox two", &check_0);
                            }
                            ImGui::EndChildPos();

  
                            ImGui::BeginChildPos("EXPLOIT", ImVec2(267, 210));
                            {

                                ImGui::Combo("Combobox ", &selectedItem1, items1, 4);

                            }
                            ImGui::EndChildPos();


                        }
                        ImGui::EndGroup();

                        ImGui::SameLine(0, 20); // 1, 2

                        ImGui::BeginGroup();
                        {

                            ImGui::BeginChildPos("MAIN", ImVec2(267, 242));
                            {

                                ImGui::Checkbox("Checkbox ", &check_1);

                                ImGui::ColorEdit4("Colorpicker##0", (float*)&color_edit, ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

                                ImGui::Keybind("Binderbox", &key0, true);

                                if (ImGui::Button("Button", ImVec2(227, 37)));

                            }
                            ImGui::EndChildPos();


                            ImGui::BeginChildPos("SETTINGS", ImVec2(267, 180));
                            {

                                ImGui::SliderInt("Slider", &slider_two, 1, 100, "%du/s");

                                ImGui::MultiCombo("Multi Combo", multi_items_count, multi_items, 5);

                            }
                            ImGui::EndChildPos();


                            ImGui::BeginChildPos("HEADER", ImVec2(267, 280));
                            {

                                ImGui::SliderFloat("Slider Float", &slider_three, -1.f, 1.f, "%.1f");

                                ImGui::RangeSliderInt("Slider Range", min0, max0, ilow0, ihigh0);

                            }
                            ImGui::EndChildPos();


                            ImGui::BeginChildPos("WORLD", ImVec2(267, 190));
                            {

                                ImGui::RangeSliderFloat("Slider Range ", min2, max2, ilow2, ihigh2);

                            }
                            ImGui::EndChildPos();


                        }

                        ImGui::EndGroup(); // END GROUP
                    }
                    else if (active_tab == 0 && active_subtab == 1) {

                        ImGui::BeginGroup();
                        {
                            ImGui::BeginChildPos("Child One", ImVec2(267, 210));
                            {

                            }
                            ImGui::EndChildPos();

                            ImGui::BeginChildPos("Child Three", ImVec2(267, 300));
                            {

                            }
                            ImGui::EndChildPos();

                            ImGui::BeginChildPos("Child Five", ImVec2(267, 110));
                            {

                            }
                            ImGui::EndChildPos();

                            ImGui::BeginChildPos("Child Seven", ImVec2(267, 180));
                            {

                            }
                            ImGui::EndChildPos();
                        }
                        ImGui::EndGroup();

                        ImGui::SameLine(0, 20); // 1, 2

                        ImGui::BeginGroup();
                        {
                            ImGui::BeginChildPos("Child Two", ImVec2(267, 135));
                            {

                            }
                            ImGui::EndChildPos();

                            ImGui::BeginChildPos("Child Four", ImVec2(267, 260));
                            {

                            }
                            ImGui::EndChildPos();

                            ImGui::BeginChildPos("Child Six", ImVec2(267, 215));
                            {

                            }
                            ImGui::EndChildPos();

                            ImGui::BeginChildPos("Child Eight", ImVec2(267, 210));
                            {

                            }
                            ImGui::EndChildPos();
                        }

                        ImGui::EndGroup();

                    }
                }
                ImGui::EndChild();

                ImGui::PopStyleVar(2);

                //////////////////////////////// NAME TABS

                ImGui::SetCursorPos(ImVec2(223, 23));

                ImGui::BeginGroup();
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha* s->Alpha);

                  if (active_tab == 0) ImGui::TextColoredTabs(ImColor(c::text_hov), "A", "RageBot  > ");
                  if (active_tab == 1) ImGui::TextColoredTabs(ImColor(c::text_hov), "B", "Anti-Aim  > ");
                                            
                  if (active_tab == 3) ImGui::TextColoredTabs(ImColor(c::text_hov), "D", "Triggerbot  > ");
                  if (active_tab == 4) ImGui::TextColoredTabs(ImColor(c::text_hov), "C", "General  > ");
                  if (active_tab == 5) ImGui::TextColoredTabs(ImColor(c::text_hov), "E", "More  > ");
                                         
                  if (active_tab == 6) ImGui::TextColoredTabs(ImColor(c::text_hov), "F", "Players  > ");
                  if (active_tab == 7) ImGui::TextColoredTabs(ImColor(c::text_hov), "C", "World  > ");
                  if (active_tab == 8) ImGui::TextColoredTabs(ImColor(c::text_hov), "E", "More  > ");
                                       
                  if (active_tab == 9) ImGui::TextColoredTabs(ImColor(c::text_hov), "G", "Misc  > ");
                  if (active_tab == 10) ImGui::TextColoredTabs(ImColor(c::text_hov), "H", "Skins  > ");
                  if (active_tab == 11) ImGui::TextColoredTabs(ImColor(c::text_hov), "I", "Configs  > ");

                  ImGui::PushStyleVar(ImGuiStyleVar_Alpha, subtab_alpha* s->Alpha);

                  if (active_tab == 0 && active_subtab == 0) ImGui::TextColoredSubTabs(ImColor(c::tab_push_gradient), "Enemy");
                  if (active_tab == 0 && active_subtab == 1) ImGui::TextColoredSubTabs(ImColor(c::tab_push_gradient), "Team");
                  if (active_tab == 0 && active_subtab == 2) ImGui::TextColoredSubTabs(ImColor(c::tab_push_gradient), "Other");

                    ImGui::PopStyleVar(2);
                }
                ImGui::EndGroup();

                move_window();

            }
            ImGui::End();
        }
        ImGui::Render();
        const float clear_color_with_alpha[4] = { 0 };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}