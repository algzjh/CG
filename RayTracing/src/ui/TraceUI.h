//
// rayUI.h
//
// The header file for the UI part
//

#ifndef __rayUI_h__
#define __rayUI_h__

// who the hell cares if my identifiers are longer than 255 characters:
#pragma warning(disable : 4786)

#include <math.h>
#include "../vecmath/vec.h"
#include "../vecmath/mat.h"

#include <string>

using std::string;

class RayTracer;

class TraceUI {
public:
	TraceUI()
		: m_nDepth(0), m_nSize(150), m_nThresh(0.0),
		m_displayDebuggingInfo( false ),
		m_bsp_enabled_value(true),
		m_fresnelEnabled(false),
		m_jitter(false),
		m_nAntialiasing(1),
		m_nblurX(0.0),
		m_nblurY(0.0),
		m_nblurZ(0.0),
		m_napertureRadius(0.0),
		m_nfocalDistance(5.0),
		m_nglossiness(0.0),
		m_nareaLightSize(0.0),
		raytracer( 0 )
	{ }

	virtual int		run() = 0;

	// Send an alert to the user in some manner
	virtual void		alert(const string& msg) = 0;

	// setters
	virtual void		setRayTracer( RayTracer* r )
		{ raytracer = r; }

	// accessors:
	int		getSize() const { return m_nSize; }
	int		getDepth() const { return m_nDepth; }
	double  getThresh() const { return m_nThresh; }
	int		getAntialiasingFactor() const { return m_nAntialiasing; }
	double	getMotionBlurX() const { return m_nblurX; }
	double	getMotionBlurY() const { return m_nblurY; }
	double	getMotionBlurZ() const { return m_nblurZ; }
	double	getApertureRadius() const { return m_napertureRadius; }
	double	getFocalDistance() const { return m_nfocalDistance; }
	double	getGlossiness() const { return m_nglossiness; }
	double	getpointLightArea() const { return m_nareaLightSize; }

	void setMultithreading(bool multithread) { this->multithread = multithread; }
	bool isMultithreading() const { return multithread; }
private:
	bool multithread;

protected:
	RayTracer*	raytracer;

	int			m_nSize;				// Size of the traced image
	int			m_nDepth;				// Max depth of recursion
	double		m_nThresh;				// Threshold for adaptive termination
	int			m_nAntialiasing;
	double		m_nblurX;
	double		m_nblurY;
	double		m_nblurZ;
	double		m_napertureRadius;
	double		m_nfocalDistance;
	double		m_nglossiness;
	double		m_nareaLightSize;

	int num_threads;

	int width;
	int height;
	int nextX;
	int nextY;
	// Determines whether or not to show debugging information
	// for individual rays.  Disabled by default for efficiency
	// reasons.
	bool		m_displayDebuggingInfo;

public:
	bool		getBSPEnabled() const { return m_bsp_enabled_value; }
	bool		getFresnelEnabled() const { return m_fresnelEnabled; }
	bool		getJitterEnabled() const { return m_jitter; }
protected:
	bool		m_bsp_enabled_value;
	bool		m_fresnelEnabled;
	bool		m_jitter;

};

#endif
