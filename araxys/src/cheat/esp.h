#ifndef ESP_H
#define ESP_H

#include <vector>
#include <iostream>

class Memory;

class ESP {
	private:
		float m_x, m_y, m_z;
		std::vector<ESP> m_players;
		int playerCount = 0;
		Memory *m_memory = nullptr;

		void addPlayer(float x, float y, float z) noexcept {
			m_players.emplace_back(x, y, z);
		}

	public:
		ESP() {
			m_x = m_y = m_z = 0;
			playerCount = 0;
			m_memory = nullptr;
		}

 		ESP(float x, float y, float z) {
			m_x = x;
			m_y = y;
			m_z = z;
			playerCount = 0;
			m_memory = nullptr;
		}

		void setMemory(Memory *memory) noexcept {
			m_memory = memory;
		}

		void refreshPlayerList(void) noexcept;

		const std::vector<ESP>& getOtherPlayers() noexcept {
			return (m_players);
		}
		
		const void printPlayerPositions(void) noexcept {
			std::cout << "LocalPlayer" << m_x << "  " << m_y << "   " << m_z << "\n\n" << std::endl;
			auto size = m_players.size();
			for (int i = 0; i != size; i++) {
				std::cout << "Player " << i << " : x = " << m_players[i].m_x << " y = " << m_players[i].m_y << " z = " << m_players[i].m_z << std::endl;
			}
		}
};

#endif // ESP_H
