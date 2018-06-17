//
// GraphicalUI.h
//
// The header file for the graphical UI
//

#ifndef __GraphicalUI_h__
#define __GraphicalUI_h__

#include "Fl.H"
#include "Fl_Window.H"
#include "Fl_Menu_Bar.H"
#include "Fl_Value_Slider.H"
#include "Fl_Check_Button.H"
#include "Fl_Button.H"

#include "Fl_File_Chooser.H"		// FLTK file chooser

#include "TraceUI.h"
#include "TraceGLWindow.h"
#include "debuggingWindow.h"

class ModelerView;

class GraphicalUI : public TraceUI {
public:
	GraphicalUI();

	int run();

	void		alert( const string& msg );

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;

	Fl_Slider*			m_sizeSlider;
	Fl_Slider*			m_depthSlider;
	Fl_Slider*			m_threshSlider;
	Fl_Slider*			m_antialiasingSlider;
	Fl_Slider*			m_blurXSlider;
	Fl_Slider*			m_blurYSlider;
	Fl_Slider*			m_blurZSlider;
	Fl_Slider*			m_apertureRadiusSlider;
	Fl_Slider*			m_focalDistanceSlider;
	Fl_Slider*			m_glossinessSlider;
	Fl_Slider*			m_areaLightSlider;

	Fl_Check_Button*	m_debuggingDisplayCheckButton;
	Fl_Check_Button*	m_fresnelReflectionCheckButton;
	Fl_Check_Button*	m_bsp_enabledCheckButton;
	Fl_Check_Button*	m_glossinessCheckButton;
	Fl_Check_Button*	m_jitteringCheckButton;


	Fl_Button*			m_renderButton;
	Fl_Button*			m_stopButton;

	TraceGLWindow*		m_traceGlWindow;


	DebuggingWindow*	m_debuggingWindow;
	// member functions
	void		setRayTracer(RayTracer *tracer);

	static void stopTracing();
private:
	void updateRender();

// static class members
	static Fl_Menu_Item menuitems[];

	static GraphicalUI* whoami(Fl_Menu_* o);

	static void cb_load_scene(Fl_Menu_* o, void* v);
	static void cb_save_image(Fl_Menu_* o, void* v);
	static void cb_exit(Fl_Menu_* o, void* v);
	static void cb_about(Fl_Menu_* o, void* v);

	static void cb_exit2(Fl_Widget* o, void* v);

	static void cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_depthSlides(Fl_Widget* o, void* v);
	static void cb_threshSlides(Fl_Widget* o, void* v);
	static void cb_antialiasSlides(Fl_Widget* o, void* v);
	static void cb_blurXSlides(Fl_Widget* o, void* v);
	static void cb_blurYSlides(Fl_Widget* o, void* v);
	static void cb_blurZSlides(Fl_Widget* o, void* v);
	static void cb_apertureRadiusSlides(Fl_Widget* o, void* v);
	static void cb_focalDistanceSlides(Fl_Widget* o, void* v);
	static void cb_glossinessSlides(Fl_Widget* o, void* v);
	static void cb_areaLightSlides(Fl_Widget* o, void* v);

	static void cb_render(Fl_Widget* o, void* v);
	static void cb_stop(Fl_Widget* o, void* v);
	static void cb_fresnelReflectionCheckButton(Fl_Widget* o, void* v);
	static void cb_jitterCheckButton(Fl_Widget* o, void* v);
	static void cb_bspEnabledCheckButton(Fl_Widget* o, void* v);
	static void cb_debuggingDisplayCheckButton(Fl_Widget* o, void* v);

	static bool doneTrace;		// Flag that gets set when the trace is done
	static bool stopTrace;		// Flag that gets set when the trace should be stopped


};

#endif
