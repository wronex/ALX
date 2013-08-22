#include <vector>
#include "alx.hpp"
#include <allegro5/allegro_image.h>
using namespace alx;


//a sprite class
class Sprite {
public:
    //position
    Point<int> position;

    //velocity
    Point<int> velocity;

    //bitmap
    Bitmap bitmap;

    //Sprite
    Sprite(const Point<int> &pos, const Bitmap &bmp) : position(pos), bitmap(bmp) {
    }

    //draws the bitmap
    void draw() const {
        bitmap.draw(position.x(), position.y());
    }

    //get rect
    Rect<int> rect() const {
        return Rect<int>(position, bitmap.size());
    }
};


typedef std::shared_ptr<Sprite> SpritePtr;


size_t rnd(size_t n) {
    return rand() % n;
}


//check collision between two sprites
bool collision(const Sprite &a, const Sprite &b) {
    return a.rect().intersects(b.rect());
}


//deflects the ball off a block
void deflectBall(Sprite &ball, const Sprite &block) {
    Rect<int> ballRect = ball.rect();
    Rect<int> blockRect = block.rect();

    if (ballRect.left() == blockRect.right()) {
        ball.velocity.setX(1);
    }
    else if (ballRect.right() == blockRect.left()) {
        ball.velocity.setX(-1);
    }

    if (ballRect.top() == blockRect.bottom()) {
        ball.velocity.setY(1);
    }
    else if (ballRect.bottom() == blockRect.top()) {
        ball.velocity.setY(-1);
    }
}


//main
int main() {
    //install allegro as needed
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    //resources
    Display display(640, 480);
    EventQueue eventQueue;
    Timer timer(1./60);
    UserEventSource ues;

    //bind the resources to the event queue
    eventQueue
        .register(Keyboard::eventSource())
        .register(Mouse::eventSource())
        .register(display)
        .register(timer)
        .register(ues);

    //bitmaps
    Bitmap paddleBmp("data/paddle.bmp");
    paddleBmp.convertMaskToAlpha(Color(0xFFFFFFFF));
    Bitmap ballBmp("data/ball.bmp");
    ballBmp.convertMaskToAlpha(Color(0xFFFFFFFF));
    std::vector<Bitmap> stones;
    for(int i = 1; i <= 23; ++i) {
        stones.push_back(Bitmap(String("data/stone") + i + ".jpg"));
    }

    //blocks
    std::vector<SpritePtr> blocks;
    int stoneWidth = stones[0].width();
    int stoneHeight = stones[0].height();
    int blockCols = display.width() / stoneWidth;
    int blockRows = 2 * display.height() / 3 / stoneHeight;
    for(int j = 0; j < blockRows; ++j) {
        for(int i = 0; i < blockCols; ++i) {
            blocks.push_back(SpritePtr(new Sprite(makePoint(i * stoneWidth, j * stoneHeight), stones[rnd(stones.size())])));
        }
    }

    //paddle and ball sprites
    auto paddleStartPos = makePoint(display.width()/2 - paddleBmp.width()/2, display.height() - paddleBmp.height());
    Sprite paddle(paddleStartPos, paddleBmp);
    auto ballStartPos = makePoint(paddle.position.x() + paddleBmp.width()/2 - ballBmp.width()/2, paddle.position.y() - ballBmp.height());
    Sprite ball(ballStartPos, ballBmp);

    NativeTextLog textLog("ALX Example Debug Window");

    //the reset function
    auto reset = [&]() {
        paddle.position = paddleStartPos;
        ball.position = ballStartPos;
        ball.velocity.set(0, 0);
        MouseState mouseState;
        mouseState.retrieve();
        display.setMousePosition(display.width()/2, mouseState.mouseY());
    };


    //the update logic function
    auto updateLogic = [&]() {
        //update the ball position
        ball.position += ball.velocity;

        //invert the ball's horizontal velocity if it hits the screen horizontal end
        if (ball.position.x() == 0 || ball.position.x() == display.width() - ball.bitmap.width()) {
            ball.velocity.setX(-ball.velocity.x());
        }

        //invert the ball's vertical velocity if it hits the screen top
        if (ball.position.y() == 0) {
            ball.velocity.setY(1);
        }

        //reset the game if the ball reaches the bottom of the screen
        if (ball.position.y() == display.height()) {
            reset();
            return;
        }

        //check if the ball collides with a block
        for(auto &block : blocks) {
            if (block && collision(ball, *block)) {
                deflectBall(ball, *block);
                block.reset();
            }
        }

        //check if the ball collides with the paddle
        if (collision(ball, paddle)) {
            textLog << "collision between ball and paddle\n";
            if (ball.rect().centerX() < paddle.rect().centerX()) {
                ball.velocity.setX(-1);
            }
            else {
                ball.velocity.setX(1);
            }
            ball.velocity.setY(-1);
        }
    };

    //the function to use for drawing the current frame
    auto drawFrame = [&]() {
        //draw black background
        al_clear_to_color(Color(0));

        //draw the blocks
        for(auto &blockPtr : blocks) {
            if (blockPtr) blockPtr->draw();
        }

        //draw the paddle and ball
        paddle.draw();
        ball.draw();
    };

    //event loop
    timer.start();
    bool loop = true;
    bool redraw = false;
    while (loop) {
        //time for redraw
        if (redraw && eventQueue.isEmpty()) {
            redraw = false;
            drawFrame();
            al_flip_display();
        }

        //wait for event
        Event event = eventQueue.waitForEvent();

        //process event
        switch (event.type()) {
            //key down
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboardKeycode()) {

                    //end the loop
                    case ALLEGRO_KEY_ESCAPE:
                        loop = false;
                        break;
                }
                break;

            //mouse
            case ALLEGRO_EVENT_MOUSE_AXES:
                paddle.position.setX(std::max(0, std::min(event.mouseX() - paddle.bitmap.width()/2, display.width() - paddle.bitmap.width())));
                if (ball.velocity == Point<int>(0, 0)) {
                    ball.position.setX(paddle.position.x() + paddle.bitmap.width()/2 - ball.bitmap.width()/2);
                }
                break;

            //button down
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (ball.velocity == Point<int>(0, 0)) {
                    ball.velocity.set(1, -1);
                }
                break;

            //timer
            case ALLEGRO_EVENT_TIMER:
                if (event.timer() == timer) {
                    redraw = true;
                    updateLogic();
                }
                break;

            //display close
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                loop = false;
                break;
        }
    }

	return 0;
}
