#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;

class Front
{
private:
	Font font;
	Text start;
	Text exit;
	Music click;
	Texture texture;
	Sprite front;
	
public:
	Front()
	{
		font.loadFromFile("Fonts/Roboto-Light.ttf");
		start.setFont(font);
		start.setString("Start");
		start.setCharacterSize(100);
		start.setFillColor(Color::White);
		start.setPosition(585, 430);
		exit.setFont(font);
		exit.setString("Exit");
		exit.setCharacterSize(100);
		exit.setFillColor(Color::White);
		exit.setPosition(595, 680);
		click.openFromFile("click.wav");
		texture.loadFromFile("front.png");
		front.setTexture(texture);
	
	}
	void drawFront()
	{
		
		RenderWindow window(VideoMode(1387, 1080), "Front");
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == Mouse::Left)
					{
						if (event.mouseButton.x >= 585 && event.mouseButton.x <= 800 && event.mouseButton.y >= 430 && event.mouseButton.y <= 530)
						{
							click.play();
							sleep(seconds(1));
							window.close();
						}
						if (event.mouseButton.x >= 585 && event.mouseButton.x <= 800 && event.mouseButton.y >= 680 && event.mouseButton.y <= 780)
						{
							click.play();
							sleep(seconds(1));
							window.close();
						}
					}
				}
				
				if (event.type == Event::MouseMoved)
				{
					if (event.mouseMove.x >= 585 && event.mouseMove.x <= 800 && event.mouseMove.y >= 430 && event.mouseMove.y <= 530)
					{
						start.setFillColor(Color::Red);
					}
					else
					{
						start.setFillColor(Color::White);
					}
					if (event.mouseMove.x >= 585 && event.mouseMove.x <= 800 && event.mouseMove.y >= 680 && event.mouseMove.y <= 780)
					{
						exit.setFillColor(Color::Red);
					}
					else
					{
						exit.setFillColor(Color::White);
					}
				}
			}
			window.clear();
			window.draw(front);
			window.draw(start);
			window.draw(exit);
			window.display();
		}

	}

};
class music
{
protected:
	
	SoundBuffer buffer2;
	Sound EliminatedMusic;
	SoundBuffer buffer3;
	Sound WinningMusic;
public:
	music()
	{
		buffer2.loadFromFile("EliminatedMusic.wav");
		EliminatedMusic.setBuffer(buffer2);
		buffer3.loadFromFile("AOA.wav");
		WinningMusic.setBuffer(buffer3);
	}
	
	void playEliminatedMusic()
	{
		EliminatedMusic.play();
	}
	void playWinningMusic()
	{
		WinningMusic.play();
	}
	
	void stopEliminated()
	{
		EliminatedMusic.stop();
	}
	void stopWinning()
	{
		WinningMusic.stop();
	}
	void stopAll()
	{
		
		EliminatedMusic.stop();
		WinningMusic.stop();
	}
};

class Soldier
{
private:
    vector<RectangleShape> rectangle;
	int noOfRectangles;
    vector<Text> numbers;
    Font font;
    Texture texture;
	Texture dead;
public:
	Soldier(int noOfRectangles)
	{
		font.loadFromFile("Fonts/Roboto-Black.ttf");
		texture.loadFromFile("soldier1.png");
		dead.loadFromFile("dead.png");
		this->noOfRectangles = noOfRectangles;
	}
    void soldierInCircleWithText()
    {
        Vector2f center(600.0f, 350.0f);
        float radius = 230.0f;
        texture.loadFromFile("soldier1.png");

        for (int i = 0; i < noOfRectangles; ++i)
        {
            float angle = i * (2 * 3.14 / noOfRectangles); // Equally spaced angles
            float x = center.x + radius * cos(angle);
            float y = center.y + radius * sin(angle);

            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(100, 100));
            rect.setPosition(x, y);
            rect.setTexture(&texture);
            rectangle.push_back(rect);

            Text text;
            text.setFont(font); // Assuming you have loaded a font
            text.setString(std::to_string(i + 1)); // Assign numbers starting from 1
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);

            
            FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(x + rect.getSize().x / 2.0f, y + rect.getSize().y / 2.0f);

            numbers.push_back(text);
        }
    }
    void UpdateSoldierAndText(int toDelete)
    {
        rectangle[toDelete].setTexture(&dead);
        numbers[toDelete].setFillColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow& window) 
    {
        for (size_t i = 0; i < noOfRectangles; ++i)
        {
            window.draw(rectangle[i]);
            window.draw(numbers[i]);
        }
    }

};
template<class T>
class Node
{
private:
	T data;
	Node<T>* next;
	
public:
	Node()
	{
		next = nullptr;
	}
	Node(T data)
	{
		this->data = data;
		next = nullptr;
	}
	void setNext(Node<T>* ptr)
	{
		next = ptr;
	}
	Node<T>* getNext()
	{
		return next;
	}
	T getData()
	{
		return data;
	}
	void setData(T data)
	{
		this->data = data;
	}
};
template<class T>
class Josephus
{
private:
	Node<T>* front;
	Node<T>* rear;
	int size;
	music M1;
public:
	Josephus():M1()
	{
		front = rear = nullptr;
		size = 0;
	}
	void enqueue(T data)
	{
		Node<T>* newNode = new Node<T>(data);
		if (front == nullptr)
		{
			front = rear = newNode;
			newNode->setNext(front);
		}
		else
		{
			rear->setNext(newNode);
			rear = newNode;
			rear->setNext(front);
		}
		size++;
		
	}
	T dequeue()
	{
		if (front != nullptr)
		{
			T store{};
			Node<T>* temp = front;
			front = front->getNext();
			rear->setNext(front);
			store = temp->getData();
			delete temp;
			size--;
			return store;
		}
	}
	void JosephusSolution(int K,Soldier &obj, RenderWindow& window, Sprite a)//movement
	{
		if (K >= 0)
		{
			int selectPlayer{};
			bool isSelected = true;
			while (true)
			{
				srand(time(0));
				
				if(isSelected)
				{ 
				selectPlayer = rand() % size+1;
				isSelected = false;
				cout << "Player to start skipping : " << selectPlayer << endl;
				}
				for (int i=0;i<selectPlayer+K-1;i++)//selectPlayer+K-1 = 4 bytes
				{
					int store = dequeue();// store is taking 4 bytes
					enqueue(store);// here enqueue is not taking any memory as the persons are just shuffling
				}
				int todel = dequeue();// freeing the memory here as well todel = 4 bytes
				selectPlayer = 1;
				cout << "Player " << todel << " Eliminated" << endl;
				
				M1.playEliminatedMusic();
				window.clear();
				window.draw(a);
				obj.UpdateSoldierAndText(todel-1);
				obj.draw(window);
				window.display();
				sleep(seconds(2));
				
				if (size == 1)
				{
					cout << "Player won : ";
					M1.playWinningMusic();
					sleep(seconds(2));
					print();
					break;\
				}
				cout << "Current Players : ";//temp->getData() = 4 bytes
				print();
				M1.stopAll();
				
			}
		}
		else
		{
			cout << "Invalid Input" << endl;
			return;
		}
	}
	int getSize()
	{
		return size;
	}
	void print()
	{
		Node<T>* temp = front;
		do
		{
			cout << temp->getData()<<" ";
			temp = temp->getNext();
		}
		while (temp != front);
		cout << endl;
	}
};

int main()
{

	Front f1;
	f1.drawFront();
	Josephus<int> J1;
	int noOfSoldiers;
	cout << "How Many Soldiers Do You Wanna Add? "<<endl;
	cin >> noOfSoldiers;
	for (int i = 1; i <= noOfSoldiers; i++)
	{
		J1.enqueue(i);
	}
	int toSkip{};
	cout << "Enter the number of people you wanna skip" << endl;
	cin >> toSkip;
	J1.print();

    RenderWindow window(sf::VideoMode(1440, 810), "Josephus Game");
	window.setFramerateLimit(60);
    Soldier soldierCircle(noOfSoldiers); 
    // Create the initial circle of soldiers only once
    soldierCircle.soldierInCircleWithText();
	Texture background;
	background.loadFromFile("background.jpg");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(background);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		window.draw(Sprite(background));

        // Draw the remaining soldiers and their
        soldierCircle.draw(window);
        window.display();

        // Pause for 5 seconds
        sleep(seconds(5));

		J1.JosephusSolution(toSkip,soldierCircle,window,backgroundSprite);
		break;
    }

    return 0;
}