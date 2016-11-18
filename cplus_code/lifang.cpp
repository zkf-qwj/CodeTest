#include <iostream>
using namespace std;
class Cube
{
	public:
		void setA(int a){
			m_a = a;
		}
		int getA(){
			return m_a;
		}
		void setB(int b){
			m_b = b;
		}
		int getB(){
			return m_b;
		}
		void setC(int c){
			m_c = c;
		}
		int getC(){
			return m_c;
		}
		void setABC(int a=0,int b=0,int c=0){
			m_a = a;
			m_b = b;
			m_c = c;
		}
	public:
		int getS(){
			m_s = 2*(m_a*m_b + m_a*m_c + m_b*m_c);
			return m_s;
		}
		int getV(){
			m_v = m_a*m_b*m_c;
			return m_v;
		}
		char *cubeEqual(Cube &c1,Cube &c2){
			if (c1.getA() == c2.getA() && 
				c1.getB() == c2.getB() &&
				c1.getC() == c2.getC()){
				return "equal";
			}
			return "no equal";
		}
		char *cubeEqual(Cube &cu2){
			if (m_a == c2.getA() && 
				m_b == c2.getB() &&
				m_c == c2.getC()){
				return "equal";
			}
			return "no equal";
			
		}
	private:
		int m_a;
		int m_b;
		int m_b;
		int m_v;
		int m_s;
};
int main()
{
	Cube cube1,cube2,cube3;
	cube1.setABC(1,2,3);
	cube2.setABC(2,3,4);
	cube3.setABC(1,2,3);
	cout << cube1.cubeEqual(cube2);

	return 0;
}
