#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL.h>
#include <GLES/gl.h>

#include "sfdroid_defs.h"

#include <hardware/hardware.h>
#include <hardware/gralloc.h>
#include <system/window.h>
#include <string>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES/glext.h>

#include <wayland-client.h>

class renderer_t {
    public:
        renderer_t() : have_focus(0), window(nullptr), glcontext(nullptr), last_screen(nullptr), egl_surf(EGL_NO_SURFACE), egl_ctx(EGL_NO_CONTEXT), w_egl_window(nullptr), frames_since_focus_gained(0), my_want_to_save_screen(false) { }
        int init();
        int render_buffer(ANativeWindowBuffer *the_buffer, buffer_info_t &info);
        int get_height();
        int get_width();
        void gained_focus(bool no_delay = false);
        void lost_focus();
        uint32_t get_window_id();
        bool is_active();
        void deinit();
        void set_activity(std::string activity);
        std::string get_activity();
        bool want_to_save_screen();
        int save_screen(ANativeWindowBuffer *buffer);
        int dummy_draw(int stride, int height, int format);

    private:
        int win_width, win_height;
        GLuint dummy_tex;
        bool have_focus;

        SDL_Window *window;
        SDL_GLContext glcontext;

        int draw_raw(void *data, int width, int height, int pixel_format);
        void *last_screen;

        static EGLNativeDisplayType egl_dpy;
        EGLSurface egl_surf;
        EGLContext egl_ctx;
        struct wl_egl_window *w_egl_window;
        static int (*pfn_eglHybrisWaylandPostBuffer)(EGLNativeWindowType win, void *buffer);
        static int instances;

        int frames_since_focus_gained;

        std::string activity;

        bool my_want_to_save_screen;
};

#endif

