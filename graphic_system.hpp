#ifndef GRAPHIC_SYSTEM_HPP_XTS_INCLUDED
#define GRAPHIC_SYSTEM_HPP_XTS_INCLUDED
#include <string>
#include <SFML/Graphics.hpp>
#include "system.hpp"
#include "ruler.hpp"
#include "error_msgr.hpp"

namespace xts {

class graphic_system {
public:
	graphic_system(const ruler &ruler_arg, sf::Font &font, error_msgr &msgr);

	void resized();
	void draw(sf::RenderTarget &target);

	void snapshot();
	void undo();
	void redo();
	
	void mkline(std::vector<std::string> labels);
	void rmline(std::vector <std::string> labels);
	void mkpoint(std::string label, std::vector<double> points);
	void rmpoint(std::string label, std::vector<double> points);
	
	void dump() const;
	void dump(std::string path) const;
	void dump(std::string path, std::vector<std::string> lines) const;
	
	double time_length() const;
	
	void exit();
	bool should_exit() const;
	
private:
	void draw_label(sf::RenderTarget &target, const std::string &str, double y);
	void draw_single_line(sf::RenderTarget &target, double y);
	void draw_points(sf::RenderTarget &target, line::const_iterator begin,
	    line::const_iterator end, double y);

	system _system;
	const ruler &_ruler;
	sf::Text _label_text;
	sf::RectangleShape _line_rect;
	sf::CircleShape _point_circle;
	bool _modified, _modified_noticed, _exit;
	error_msgr &_error_msgr;
};

}
#endif
