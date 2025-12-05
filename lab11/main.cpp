#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "func.hpp"

int main() {
	std::ifstream input_file("input.txt");
	if (!input_file.is_open()) {
		std::cout << "Not open file" << std::endl;
		return 1;
	}

	std::string text;
	std::string line;
	while (std::getline(input_file, line)) {
		text += line + " ";
	}
	input_file.close();


	std::vector<std::string>words = all_words(text);

	std::vector<inf>word_info;

	for (int i = 0; i < words.size(); i++) {
		const std::string& word = words[i];
		std::string low_word = to_lower(word);
		int sogl_count = count_diff(low_word);
		word_info.push_back({ word, sogl_count });
	}
	DELETE_DUBBLE(word_info);
	main_swap(word_info);

	if (word_info.size() > 2000) {
		word_info.resize(2000);
	}

	std::ofstream output_file("output.txt");
	if (!output_file.is_open()) {
		std::cout << "Not create file output.txt" << std::endl;
		return 1;
	}

	for (int i = 0; i < word_info.size(); i++) {
		const inf& info = word_info[i];
		output_file << info.word << " " << info.sogl_count << std::endl;
	}

	output_file.close();
	std::cout << "Result wrote in file output.txt" << std::endl;
	std::cout << "Founded unique words: " << word_info.size() << std::endl;

	return 0;
}





#include <iostream>
#include "func.hpp"

const char LOWUP = 32;

bool is_alpha(char c) {
	return(c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char to_lower(char c) {
	if (c >= 'A' && c <= 'Z') {
		return c + LOWUP;
	}
	return c;
}

std::string to_lower(const std::string& s) {
	std::string result = s;
	int i = 0;
	while (i < result.length()) {
		result[i] = to_lower(result[i]);
		i++;
	}
	return result;
}


bool sogl(char c) {
	c = to_lower(c);
	const char* sogl = "bcdfghjklmnpqrstvwxyz";
	for (int i = 0; sogl[i] != '\0'; i++) {
		if (c == sogl[i]) {
			return true;
		}
	}

	return false;
}


std::vector<std::string> all_words(const std::string& text) {
	std::vector<std::string>words;
	std::string nast_word;

	for (int i = 0; i < text.length(); i++) {
		char c = text[i];

		if (is_alpha(c)) {
			nast_word += c;
		}
		else {
			if (!nast_word.empty()) {
				words.push_back(nast_word);
				nast_word.clear();
			}
		}
	}

	if (!nast_word.empty()) {
		words.push_back(nast_word);
	}
	return words;
}


int count_diff(const std::string& word) {
	bool seen[26] = { false };
	int count = 0;

	for (int i = 0; i < word.length(); i++) {
		char c = word[i];

		if (sogl(c)) {
			int index = to_lower(c) - 'a';
			if (!seen[index]) {
				seen[index] = true;
				count++;
			}
		}
	}
	return count;
}


void DELETE_DUBBLE(std::vector<inf>& words) {
	std::vector<inf>un_words;

	for (int i = 0; i < words.size(); i++) {
		const inf& info = words[i];
		bool found = false;
		std::string lower_nast = to_lower(info.word);

		for (int j = 0; j < un_words.size(); j++) {
			if (to_lower(un_words[j].word) == lower_nast) {
				found = true;
				break;
			}
		}

		if (found == false) {
			un_words.push_back(info);
		}
	}
	words = un_words;
}

void swap(inf& a, inf& b) {
	inf trp = a;
	a = b;
	b = trp;
}



bool yesorno(const inf& a, const inf& b) {
	if (a.sogl_count != b.sogl_count) {
		return a.sogl_count < b.sogl_count;
	}

	return to_lower(a.word) > to_lower(b.word);
}


void main_swap(std::vector<inf>& words) {
	int n = words.size();
	bool swapp;

	for (int i = 0; i < n - 1; i++) {
		swapp = false;

		for (int j = 0; j < n - i - 1; j++) {
			if (yesorno(words[j], words[j + 1])) {
				swap(words[j], words[j + 1]);
				swapp = true;
			}
		}

		if (swapp == false) {
			break;
		}
	}
}





#pragma once
#include <string>
#include <vector>

struct inf {
	std::string word;
	int sogl_count;
};


bool is_alpha(char c);
char to_lower(char c);
std::string to_lower(const std::string& s);
bool sogl(char c);
std::vector<std::string> all_words(const std::string& text);
int count_diff(const std::string& word);
void DELETE_DUBBLE(std::vector<inf>& words);
void swap(inf& a, inf& b);
bool yesorno(const inf& a, const inf& b);
void main_swap(std::vector<inf>& words);






/*Did you know that there’s a World Chocolate Day ? It takes place each year on 7 July.To celebrate it, read about the history of chocolate and the interesting journey from cocoa bean to chocolate bar.Chocolate was first used as a drink over 3, 500 years ago in Central America.It was very popular with the Mayans and the Aztecs, who mixed cocoa beans with vanilla or chilli peppers.In fact, cocoa beans were so important to them that they were used as money.Cocoa was first grown in Ecuador, which was, for a long time, the world’s number - one producer of cocoa beans.It is still one of the top ten producers of the beans, but nowadays more than 70 per cent of cocoa beans come from West Africa.
Cocoa beans come from cocoa trees.These trees grow in tropical forests around the world, from South America to Indonesia.The beans grow in colourful pods of red, yellow and purple.Inside the pods are the beans.Each tree grows around 50 pods a year, and each pod can contain between 20 and 60 beans.It takes around 100 beans to make 100 grams of chocolate.The pods are picked by hand to protect the trees.Once the pods are picked from the tree, they are opened and the beans are taken out.The beans need to go through a number of different processes before they are ready to be turned into chocolate.First, the beans and the pulp are placed in special boxes, where they slowly ferment for up
to five days.Here the beans turn brown and start to develop their special flavour.They are then put out in the sun to dry for approximately 14 days.After this, they are roasted for about 15 minutes in preparation for the final stage, when the beans are taken out of their shells.At the end of this process, we are left with the cocoa ‘nibs’ – chocolate in its purest form and the basic ingredient for all chocolate products.The first step is to grind the nibs by machine or between two large stones.This produces cocoa liquor, a semi - solid paste.This is then cooked and mixed continuously for hours or even days until it is just right.This is also the stage at which other ingredients are
added : sugar, milk, various flavours.Interestingly, chocolate melts at 34C.This is just below body temperature, which explains why it can be so sticky and messy, but also why it melts as soon as you put it in your mouth.At this point the cocoa nibs are ready for the last stage in the journey.For the cocoa liquor to turn into solid chocolate, it needs to be heated and cooled and heated again until it forms a solid mass.And so, at last, the journey from bean to bar is complete.So now you know all about how chocolate is made, you may want to celebrate the day by eating one of your favourite chocolate treats!It's a huge festival that takes place at Worthy Farm, in the countryside near the
town of Glastonbury in south - west England.It began in 1970 when Michael Eavis, a local farmer, organised a small music festival on his farm.Back then, tickets cost £1 and they included free milk from the farm!Today, the festival is run by Eavis's youngest daughter, Emily Eavis, and it has grown into a five-day festival with around 200,000 people attending. Tickets normally sell out minutes after going on sale, but if you can't get a ticket, you can still watch the performances live on television.The festival staff are volunteers, and every year it raises millions of pounds for charity.The festival site is enormous, the size of over 500 football pitches.Festival - goers camp on the
festival site and they can choose from different areas with different atmospheres.Some are quiet, some are lively and some are for families.The site has food stalls, bars, toilets, a medical centre, a church, a cinema, recycling facilities and much more.Glastonbury even has its own newspaper printed on the site!You can hear rock, pop, hip - hop and many other kinds of music.The biggest stage is called the Pyramid Stage, and that is where the most famous bands and singers play, which have included the Rolling Stones, Shakira, Beyoncé and Coldplay.On smaller stages you can see less famous artists.In total there are thousands of performances over the five days of the festival, on over a
hundred stages.Apart from music, you can also see comedy, theatre and circus performances.Glastonbury promotes environmental protection.The festival site uses solar power, wind power and other renewable energies to reduce its environmental impact, and power generators on the site use fuel made from waste cooking oil.To reduce waste on the site, reusable or compostable plates and cups are used instead of plastic ones, and single - use plastic bottles aren't allowed. The festival even takes a break once every five or six years to let the land and local people recover from the huge festival.We can't talk about Glastonbury without talking about the weather.The festival is in June, but the
weather is unpredictable, with rain and storms sometimes.People still have fun by splashing around in the water and mud!This special day for music originated in France and was first celebrated in Paris in 1982. Since then, its popularity has spread all over the globe, and now World Music Day is celebrated on the same day in more than 1, 000 cities in 120 countries, including India, Italy, Australia, Peru, Canada, the UK and Japan.This festival has different names in different countries, for example 'La Fête de la Musique' in France, 'Make Music Day' in the UK, 'Festa della Musica' in Italy or 'Swieto Muzyki' in Poland.Back in 1982, a survey in France showed that five million people
(approximately 9 per cent of the population at the time) played a musical instrument.The Minister for Art and Culture, Jack Lang, and Maurice Fleuret, a composer, decided to find a way to get as many people as possible playing music for everyone to hear.They launched 'La Fête de la Musique'.There is a play on words in the name : La Fête de la Musique means 'Music festival' and 'Faites de la musique' (pronounced in the same way) means 'Make music!'On this day, people listen to and play music in their local area.You can listen to music in the street, outside bars and cafés, in parks and other public spaces.You don't have to pay for these concerts – the musicians play for free. World 
Music Day encourages all amateur and professional musicians, young and old, to perform and it aims to make all genres of music available to the public.As all music genres are encouraged on World Music Day, you could listen to a jazz band, a rock group, an orchestra, a choir, a samba band, a reggae sound system or a techno DJ … whoever happens to be playing in your local area.It's a great way to discover types of music that you didn't know – for free!If there are no World Music Day events where you live or if you are unable to attend face - to - face, there are lots of online events which take place on this special day.Live - streamed events such as the day - long Make Music Global Livestream
make it possible to discover and enjoy live music from all over the world.Happy World Music Day!Friends come in all shapes and sizes.They may be someone we met as a child, a classmate at school, someone we met at work or through other friends.They may be friends who live at a distance in another country or virtual friends we've made online. Whoever they are, however we met them, there is a special connection based on a shared history and interests, enjoying doing things together or simply talking and understanding each other. Friends are there to help us at difficult times and to celebrate the good times. Doctors say that friends are very important for both our physical and mental 
health at all stages in life.But friends are not only important on an individual level.Friendship can also be important on a global level.Friendships that cross borders can help bring peace and avoid war.Learning to think of other people, people who are different from us, as our friends helps us work together to build a culture of peace.That's why the UN declared 30 July as its official International Day of Friendship.An international celebration was first suggested by the World Friendship Crusade. This organisation was founded by Dr Ramón Artemio Bracho and his friends in Puerto Pinasco, Paraguay, in 1958. They wanted to support the power of friendship and its importance in creating
a culture of peace.So, in the same year, they decided to celebrate Friendship Week in Puerto Pinasco and other places in Paraguay.The following year, they repeated the week and finished on 30 July, which they declared as Friendship Day.From there, celebrations of friendship grew and spread across the Americas, then the world, and eventually the UN declared an International Day of Friendship in 2011.The International Day of Friendship on 30 July is not the only day celebrating friendship around the world.A number of countries, such as Paraguay, also celebrate on 30 July, but other countries have different dates.For example, Argentina, Brazil and Spain celebrate Friend's Day on 20 July,
while in India and the US, they celebrate it on the first Sunday in August.In Finland and Estonia, Friendship Day is celebrated on the same day as Valentine's Day, 14 February.Wherever it's celebrated, the celebrations are very similar.Friends meet up to spend time together.They may eat out or have a meal at home.They give each other small gifts : books, flowers, simple jewellery such as a friendship band(a simple bracelet).Some people send each other cards and greetings online.Whatever form the celebration takes, the spirit is the same – to remember the importance of friends and the power of friendship.the United Nations, 19 August is a day to reflect.It was on this day in 2003*/
