
#include "Button.h"
#include <UIFactory.h> 


using namespace uth;
using namespace pmath;

Button::Button(const ButtonCallback& callback)
	:Component("clickButton")
	,m_Type(ButtonType::Click)

{
}

Button::Button(ButtonType type, const ButtonCallback& callback)
	: Component("generalButton")
	, m_Type(type)
	, m_callback(callback)
{
}


void Button::Init()
{
}

void Button::Draw(uth::RenderTarget& target)
{
}

void Button::Update(float delta)
{
	const auto& type = uthInput.Common.Event();
	const auto& wnd = uthEngine.GetWindow();
	const auto area = parent->transform.GetLocalBounds();
	const bool wasPressed = m_isPressed;

#if defined(UTH_SYSTEM_WINDOWS)

	const auto pos = wnd.PixelToCoords(uthInput.Mouse.Position());

	if (type == InputEvent::STATIONARY)
	{
		if (area.contains(pos) && !m_isPressed)
		{
			if (m_Type == ButtonType::Click)
			{
				m_isPressed = true;
			}
			else if (m_Type == ButtonType::Toggle)
			{
				m_isPressed = true;
			}
		}
	}
	else if (type == InputEvent::CLICK)
	{
		if (area.contains(pos) && m_isPressed)
		{
			if (m_Type == ButtonType::Click)
			{
				m_isPressed = false;
			}
			else if (m_Type == ButtonType::Toggle)
			{
				if (m_isToggled)
				{
					m_isToggled = false;
					m_isPressed = false;
				}
				else if (m_isPressed)
				{
					m_isToggled = true;
				}
			}

			if (m_callback != nullptr)
			{
				m_callback(*parent);
			}
		}
		else
		{
			m_isPressed = m_isToggled;
		}
	}

	
	/**
	else if (type == InputEvent::NONE)
	{
		m_isPressed = false;
	}
	/**/

#elif defined(UTH_SYSTEM_ANDROID)


const auto pos = wnd.PixelToCoords(uthInput.touch[0].Position());

if (type == InputEvent::STATIONARY)
{
	if (area.contains(pos) && !m_isPressed)
	{
		if (m_Type == ButtonType::Click)
		{
			m_isPressed = true;
		}
		else if (m_Type == ButtonType::Toggle)
		{
			m_isPressed = true;
		}
	}
}
else if (type == InputEvent::CLICK)
{
	if (area.contains(pos) && m_isPressed)
	{
		if (m_Type == ButtonType::Click)
		{
			m_isPressed = false;
		}
		else if (m_Type == ButtonType::Toggle)
		{
			if (m_isToggled)
			{
				m_isToggled = false;
				m_isPressed = false;
			}
			else if (m_isPressed)
			{
				m_isToggled = true;
			}
		}

		if (m_callback != nullptr)
		{
			m_callback(*parent);
		}
	}
	else
	{
		m_isPressed = m_isToggled;
	}
	}


#endif

	if (wasPressed != m_isPressed)
	{
		Sprite& sprite = *parent->GetComponent<Sprite>();

		if (m_isPressed)
		{
			sprite.SetColor(0.75f, 0.75f, 0.75f, 1.0f);
		}
		else
		{
			sprite.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
}

void Button::updateColor()
{
	Sprite& sprite = *parent->GetComponent<Sprite>();

	if (m_isPressed)
	{
		sprite.SetColor(0.75f, 0.75f, 0.75f, 1.0f);
	}
	else
	{
		sprite.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

bool Button::isPressed() const
{
	return m_isPressed;
}

void Button::reset()
{
	m_isPressed = false;
	m_isToggled = false;
	updateColor();
}