#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <iostream>


class Animator
{
public:
	Animator();
	~Animator();

	void SetSprite(sf::Sprite& sprite);
	//bool AddAnimationState(std::string name, TextureAtlas& atlas, size_t begin, size_t end, bool autoPlay = false);
	bool AddAnimationState(std::string name, sf::Texture& texture, size_t begin, size_t end, bool autoPlay = false);
	bool AddAnimationState(std::string name, sf::Texture& texture, bool autoPlay = false);
	bool ChangeActiveState(const std::string& name);

	std::string GetActiveState() const;

	void SetAnimationSpeed(float speed);
	void SetDelayBetweenFrames(float delay);
	void SetLoop(bool loop);

	/// Updates animation state
	void Animate(float);
	/// Check anim playing state
	bool IsPlaying();
	/// Resume animation
	void Play();
	/// Pause animation
	void Pause();
	/// Stop animation and set current frame to 0
	void Stop();

private:
	struct AnimationStateInfo
	{
		sf::Texture texture;
		size_t beg; // first frame (inclusive)
		size_t end; // last frame (inclusive)
	};

	std::map<std::string, AnimationStateInfo> m_states;
	std::map<std::string, sf::Texture> states;
	std::map<std::string, AnimationStateInfo>::iterator m_statesIterator;
	std::map<std::string, sf::Texture>::iterator statesIterator;


	std::string m_activeStateName;
	AnimationStateInfo* m_activeStateInfo;
	sf::Texture currTexture;

	float m_animationSpeed;
	float m_delay;
	float m_elapsedTime;
	float m_timeToChangeFrame;

	size_t m_currentFrame;
	size_t m_lastFrame;

	bool m_loop;
	bool m_animIsPlaying;

	sf::Sprite* m_sprite;
};