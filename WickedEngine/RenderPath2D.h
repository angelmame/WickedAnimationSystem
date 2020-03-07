#pragma once
#include "RenderPath.h"
#include "wiGUI.h"

#include <string>

class wiSprite;
class wiFont;

struct RenderItem2D
{
	enum TYPE
	{
		SPRITE,
		FONT,
	} type;
	wiSprite* sprite = nullptr;
	wiFont* font = nullptr;
	int order = 0;
};
struct RenderLayer2D
{
	std::vector<RenderItem2D> items;
	std::string name;
	int order = 0;
};

class RenderPath2D :
	public RenderPath
{
private:
	wiGraphics::Texture rtStenciled;
	wiGraphics::Texture rtFinal;

	wiGraphics::RenderPass renderpass_stenciled;
	wiGraphics::RenderPass renderpass_final;

	wiGUI GUI;
	float spriteSpeed = 1.0f;

protected:
	void ResizeBuffers() override;
public:

	void Initialize() override;
	void Load() override;
	void Unload() override;
	void Start() override;
	void Update(float dt) override;
	void FixedUpdate() override;
	void Render() const override;
	void Compose(wiGraphics::CommandList cmd) const override;

	const wiGraphics::Texture& GetRenderResult() const { return rtFinal; }
	virtual const wiGraphics::Texture* GetDepthStencil() const { return nullptr; }

	void AddSprite(wiSprite* sprite, const std::string& layer = "");
	void RemoveSprite(wiSprite* sprite);
	void ClearSprites();
	void SetSpriteSpeed(float value) { spriteSpeed = value; }
	float GetSpriteSpeed() { return spriteSpeed; }
	int GetSpriteOrder(wiSprite* sprite);

	void AddFont(wiFont* font, const std::string& layer = "");
	void RemoveFont(wiFont* font);
	void ClearFonts();
	int GetFontOrder(wiFont* font);

	std::vector<RenderLayer2D> layers{ 1 };
	void AddLayer(const std::string& name);
	void SetLayerOrder(const std::string& name, int order);
	void SetSpriteOrder(wiSprite* sprite, int order);
	void SetFontOrder(wiFont* font, int order);
	void SortLayers();
	void CleanLayers();

	const wiGUI& GetGUI() const { return GUI; }
	wiGUI& GetGUI() { return GUI; }
};

