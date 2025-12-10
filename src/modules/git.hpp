/**
 * @file git.hpp
 * @authors MarioS271
 */

#include <windows.h>
#include "panel.hpp"
#include "screen.hpp"
#include "anchors.hpp"
#include "colors.hpp"
#include "constants.hpp"

class GitPanel : public Panel {
public:
    void redraw(Renderer &r) override {
        COORD size = {
            screen::width(),
            static_cast<SHORT>(screen::height() - 2),
        };
        COORD anchor_lu = {
            anchor::topLeft().X,
            static_cast<SHORT>(anchor::topLeft().Y + 1),
        };
        r.clearArea(anchor_lu, size);

        COORD pos = anchor::center();
        pos.X -= 5;

        r.drawText(pos, L"Git Content", Colors::Fg::red | Colors::Fg::intense);
    }
};