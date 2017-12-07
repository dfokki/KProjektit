#ifndef BUTTON_H
#define BUTTON_H

#include <UtH/UtHEngine.hpp>

enum class ButtonType
{
	Click,
	Toggle
};

typedef std::function<void(uth::GameObject&)> ButtonCallback;

class Button : public uth::Component
{

public:
	Button() = default;
	Button(const ButtonCallback&);
	Button(ButtonType, const ButtonCallback&);
	~Button() = default;

	void Init() override;
	void Draw(uth::RenderTarget& target) override;
	void Update(float delta) override;

	void updateColor();
	bool isPressed() const;
	void reset();
private:
	bool m_isPressed = false;
	bool m_isToggled = false;
	const ButtonType m_Type;
	ButtonCallback    m_callback;
};

#endif // !BUTTON_H