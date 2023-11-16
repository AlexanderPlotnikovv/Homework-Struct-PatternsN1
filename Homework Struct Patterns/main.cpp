#include <iostream>
#include <algorithm>

class Text
{
public:
	virtual void render(std::string& data)
	{
		std::cout << data;
	}
};

class DecoratedText : public Text
{
public:
	Text* text;
	explicit DecoratedText(Text* text) : text(text) {}
};

class BoldText : public DecoratedText
{
public:
	BoldText(Text*boldtext) : DecoratedText(boldtext) {}
	void render(std::string& data) override
	{
		std::cout << "<b>";
		text->render(data);
		std::cout << "</b>";
	}
};

class ParagraphText : public DecoratedText
{
public:
	ParagraphText(Text* ptext) : DecoratedText(ptext) {}
	void render(std::string& data)
	{
		std::cout << "<p>";
		text->render(data);
		std::cout << "</p>";
	}
};

class ReversedText : public DecoratedText
{
public:
	ReversedText(Text* ptext) : DecoratedText(ptext) {}
	void render(std::string& data)
	{
		std::reverse(data.begin(), data.end());
		text->render(data);
	}
};

class Link : public DecoratedText
{
public:
	Link(Text* ptext) : DecoratedText(ptext) {}
	void render(std::string& data, std::string& str)
	{
		std::cout << "<a href=";
		std::cout << data;
		std::cout << ">";
		text->render(str);
		std::cout << "</a>";
	}
};

int main()
{
	std::string str = "I bought new mansion for 10000000$";
	std::string link = "youtube.com";
	auto text = new Link(new ParagraphText(new ReversedText(new Text())));
	text->render(link, str);
	return 0;
}