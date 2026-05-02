#include <string>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <array>

using namespace std::literals::chrono_literals;

// Paleta de colores extendida para la interfaz
std::string const TERM_GREEN_COLOUR           {"\x1b[32m"};
std::string const TERM_RED_COLOUR             {"\x1b[31m"};
std::string const TERM_YELLOW_COLOUR          {"\x1b[33m"};
std::string const TERM_CYAN_COLOUR            {"\x1b[36m"};
std::string const TERM_NORMAL_COLOUR          {"\x1b[0m"};

std::string const TERM_CLEAR_SCREEN           {"\033[2J\033H"};
std::string const TERM_POSITION_CURSOR_ON_TOP {"\033[H"};

std::chrono::microseconds constexpr WRITE_SPEED_NORMAL { 50'000us};
std::chrono::microseconds constexpr WRITE_SPEED_FAST   { 15'000us};
std::chrono::microseconds constexpr WRITE_SPEED_SLOW   {100'000us};

enum class Application_state {
  BOOT,
  MENU,
  INBOX,
  INBOX_READ_MESSAGE,
  CHRONICLE,
  CREDITS,
  SHUTDOWN
};

void write_message(std::string const& message, std::chrono::microseconds time) {
  for (auto const c : message) {
    std::cout << c;
    std::fflush(stdout);
    std::this_thread::sleep_for(time);
  }
}

Application_state process_boot() {
  std::cout << TERM_GREEN_COLOUR << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  write_message("Inicializando IreneLuis-OS v1.0...\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(800ms);

  write_message("[OK] Búfers de memoria: +300 días de historia encontrados.\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(800ms);

  write_message("[OK] Sincronización de hardware establecida.\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_CYAN_COLOUR;
  write_message("[EN CURSO] Buscando presencias de Irene y Luis en la red local...\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(2'000ms);

  std::cout << TERM_GREEN_COLOUR;
  write_message("[ENCONTRADO] Conexión segura establecida.\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_CYAN_COLOUR;
  write_message("\n[BIENVENIDA] Bienvenidos de vuelta, Irene y Luis.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_NORMAL_COLOUR;

  return Application_state::MENU;
}

Application_state process_menu() {
  std::cout << TERM_GREEN_COLOUR << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  int option {-1};
  bool quit {false};
  int current_quote_index = 0;
  std::array<std::string, 5> quotes = {
    "Hoy estás radiante.",
    "La vida te devolverá el bien que le hiciste a otras personas.",
    "No dejes de soñar y de esforzarte como lo estás haciendo últimamente.",
    "¡Qué sería del sol si no tuviera personas como vos sobre las que brillar!",
    "Nunca dejaré de apoyarte.",
  };

  std::cout << TERM_CYAN_COLOUR;
  write_message("+------------------------------------+\n", WRITE_SPEED_FAST);
  write_message("|           MENÚ PRINCIPAL           |\n", WRITE_SPEED_FAST);
  write_message("+------------------------------------+\n", WRITE_SPEED_FAST);
  std::cout << TERM_GREEN_COLOUR;
  write_message("|  1. Revisar bandeja de correo.     |\n", WRITE_SPEED_FAST);
  write_message("|  2. Recibir recordatorio random.   |\n", WRITE_SPEED_FAST);
  write_message("|  3. Apagar sistema.                |\n", WRITE_SPEED_FAST);
  std::cout << TERM_CYAN_COLOUR;
  write_message("+------------------------------------+\n", WRITE_SPEED_FAST);
  std::cout << TERM_NORMAL_COLOUR;

  while (!quit) {
    write_message("\n> Elige una opción: ", WRITE_SPEED_FAST);
    std::cin >> option;

    switch (option) {
    case 1:
      quit = true;
      break;
    case 2:
      std::cout << TERM_YELLOW_COLOUR;
      write_message("\n[SISTEMA]: " + quotes[current_quote_index] + "\n", WRITE_SPEED_NORMAL);
      std::cout << TERM_NORMAL_COLOUR;
      std::this_thread::sleep_for(1'500ms);
      current_quote_index = (current_quote_index + 1) % quotes.size();
      break;
    case 3:
      return Application_state::SHUTDOWN;
    default:
      std::cout << TERM_RED_COLOUR;
      write_message("[ERROR] Opción incorrecta. Inténtalo de nuevo.\n", WRITE_SPEED_FAST);
      std::cout << TERM_NORMAL_COLOUR;
    }
  }

  return Application_state::INBOX;
}

Application_state process_inbox() {
  char option;
  bool quit {false};
  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  std::cout << TERM_CYAN_COLOUR;
  write_message("+==========================================================================+\n", WRITE_SPEED_FAST);
  write_message("|              BANDEJA DE ENTRADA DE IRENE - IreneLuisOS v1.0              |\n", WRITE_SPEED_FAST);
  write_message("+============+=============+===============================================+\n", WRITE_SPEED_FAST);
  write_message("| ESTADO     | REMITENTE   | ASUNTO                                        |\n", WRITE_SPEED_FAST);
  write_message("+------------+-------------+-----------------------------------------------+\n", WRITE_SPEED_FAST);

  std::cout << TERM_RED_COLOUR;
  write_message("| [NUEVO!]   | [ADM]       | Urgente: sobrecarga en el núcleo.             |\n", WRITE_SPEED_FAST);

  std::cout << TERM_GREEN_COLOUR;
  write_message("| [LEÍDO]    | [Anna]      | El caballo m'ha mirao' mal...                 |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Anna]      | Estoy hasta el coño de las oposiciones.       |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Luis]      | Sobre las sustancias...                       |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Luis]      | Vamo' arribaaaaaaaaaaaa!                      |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Jalima]    | Cariño, mira, que al final no podré ir...     |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Jalima]    | Cariño, yo me apunto a la fiesta!             |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Salva]     | Ay, la Kovaaaaaaaaaaaaaaaaaaaaaa!             |\n", WRITE_SPEED_FAST);

  std::cout << TERM_CYAN_COLOUR;
  write_message("+============+=============+===============================================+\n\n", WRITE_SPEED_FAST);

  std::cout << TERM_YELLOW_COLOUR;
  write_message("[INFO] Presiona [E] + [Intro] para leer el mensaje urgente.\n", WRITE_SPEED_FAST);
  std::cout << TERM_NORMAL_COLOUR;

  while (!quit) {
    std::cout << "> ";
    std::cin >> option;

    if (option == 'e' || option == 'E') {
      quit = true;
    }
  }

  return Application_state::INBOX_READ_MESSAGE;
}

Application_state process_inbox_read_message() {
  char option;
  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  std::cout << TERM_RED_COLOUR;
  write_message("=======================================================================\n", WRITE_SPEED_FAST);
  write_message("[!] ADVERTENCIA CRÍTICA DEL SISTEMA: TEMPERATURA DE LA CPU AL 98°C [!]\n", WRITE_SPEED_NORMAL);
  write_message("=======================================================================\n\n", WRITE_SPEED_FAST);

  std::cout << TERM_YELLOW_COLOUR;
  write_message("[MOTIVO] Sobrecarga térmica detectada.\n", WRITE_SPEED_FAST);
  write_message("[INFO] Escaneando árbol de procesos activos en la memoria de Irene...\n\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'000ms);

  // Tabla estilo 'htop' para un efecto más técnico e inmersivo
  std::cout << TERM_CYAN_COLOUR;
  write_message("+--------------------+---------+--------+----------+\n", WRITE_SPEED_FAST);
  write_message("| PROCESO            | DUEÑO   | % CPU  | ESTADO   |\n", WRITE_SPEED_FAST);
  write_message("+--------------------+---------+--------+----------+\n", WRITE_SPEED_FAST);
  std::cout << TERM_GREEN_COLOUR;
  write_message("| inteligencia       | irene   |  12.5% | ÓPTIMO   |\n", WRITE_SPEED_FAST);
  write_message("| empatía            | irene   |  18.0% | ÓPTIMO   |\n", WRITE_SPEED_FAST);
  write_message("| belleza            | irene   |  20.0% | ÓPTIMO   |\n", WRITE_SPEED_FAST);
  write_message("| resiliencia        | irene   |  15.2% | ÓPTIMO   |\n", WRITE_SPEED_FAST);
  write_message("| optimismo          | irene   |  10.1% | ÓPTIMO   |\n", WRITE_SPEED_FAST);
  write_message("| amabilidad         | irene   |  14.2% | ÓPTIMO   |\n", WRITE_SPEED_FAST);

  std::cout << TERM_RED_COLOUR;
  std::this_thread::sleep_for(500ms);
  write_message("| validación_externa | irene   |  99.9% | CRÍTICO  |\n", WRITE_SPEED_SLOW);

  std::cout << TERM_CYAN_COLOUR;
  write_message("+--------------------+---------+--------+----------+\n", WRITE_SPEED_FAST);

  std::cout << TERM_YELLOW_COLOUR;
  write_message("\n[!][DIAGNÓSTICO] El proceso 'validación_externa' está drenando tu energía.\n", WRITE_SPEED_NORMAL);
  write_message("Tu carga actual es demasiado pesada de llevar sola.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_CYAN_COLOUR;
  write_message("\n[REMEDIO] Requiere intervención manual para estabilizar.\n", WRITE_SPEED_FAST);
  write_message("¿Autorizas al administrador a iniciar el protocolo de reparación? (S/N)\n", WRITE_SPEED_FAST);
  std::cout << TERM_NORMAL_COLOUR;

  while (true) {
    std::cout << "> ";
    std::cin >> option;

    if (option == 's' || option == 'S') {
      break;
    }

    if (option == 'n' || option == 'N') {
      std::cout << TERM_YELLOW_COLOUR;
      write_message("El sistema no acepta un 'No' como respuesta cuando se trata de cuidarte :)\n", WRITE_SPEED_FAST);
      std::cout << TERM_NORMAL_COLOUR;
    }
  }

  std::cout << TERM_GREEN_COLOUR;
  write_message("\n[INICIANDO REPARACIÓN...]\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  return Application_state::CHRONICLE;
}

Application_state process_chronicle() {
  std::string input;
  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  std::cout << TERM_YELLOW_COLOUR;
  write_message("[SISTEMA] Forzando el cierre del proceso 'validación_externa'...\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);
  std::cout << TERM_GREEN_COLOUR;
  write_message("[OK] Proceso terminado con éxito.\n", WRITE_SPEED_FAST);
  write_message("[OK] Liberando memoria... Temperatura reduciéndose a niveles estables.\n\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_NORMAL_COLOUR;
  write_message("Irene...\n", WRITE_SPEED_SLOW);
  std::this_thread::sleep_for(1'500ms);

  write_message("Los registros del sistema indican que a veces la pantalla se vuelve demasiado oscura.\n", WRITE_SPEED_NORMAL);
  write_message("Que intentas apagar la luz para no ver el reflejo en el monitor.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(2'500ms);

  write_message("\nPero no necesitas operar al 200% todo el tiempo para que este sistema te considere perfecta.\n", WRITE_SPEED_NORMAL);
  write_message("Tus procesos principales funcionan con una fluidez asombrosa. Sos increíble.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(2'500ms);

  std::cout << TERM_CYAN_COLOUR;
  write_message("\n[ACCIÓN REQUERIDA] Para estabilizar la CPU permanentemente y volver a encender la luz, por favor, confirma los nuevos parámetros.\n", WRITE_SPEED_FAST);
  std::cout << TERM_YELLOW_COLOUR;
  write_message("Escribe: SOY SUFICIENTE Y ESTOY CRECIENDO\n", WRITE_SPEED_NORMAL);
  std::cout << TERM_NORMAL_COLOUR;

  while (true) {
    std::cout << "\n> ";
    std::getline(std::cin >> std::ws, input);

    if (input == "SOY SUFICIENTE" || input == "soy suficiente" || input == "SOY SUFICIENTE Y ESTOY CRECIENDO" || input == "soy suficiente y estoy creciendo") {
      break;
    } else {
      std::cout << TERM_RED_COLOUR;
      write_message("[ERROR DE VALIDACIÓN] El sistema sabe que esa no es la verdad. Inténtalo de nuevo, creyéndotelo un poco más.\n", WRITE_SPEED_FAST);
      std::cout << TERM_NORMAL_COLOUR;
    }
  }

  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;
  std::cout << TERM_CYAN_COLOUR;
  write_message("[SISTEMA RESTAURADO Y ESTABILIZADO]\n\n", WRITE_SPEED_SLOW);
  std::cout << TERM_NORMAL_COLOUR;
  write_message("Luz encendida. Estás lista para brillar.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(3'000ms);

  return Application_state::CREDITS;
}

Application_state process_credits() {
  std::cout << TERM_CYAN_COLOUR << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  write_message("==========================================================================\n", WRITE_SPEED_FAST);
  write_message("                              C R É D I T O S                             \n", WRITE_SPEED_FAST);
  write_message("==========================================================================\n\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(500ms);

  std::cout << TERM_NORMAL_COLOUR;
  write_message("> Programa hecho por: Luis\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(800ms);

  write_message("> Inspiración: Irene (la persona más deslumbrante que conozco)\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(800ms);

  write_message("> Fecha: 2026-04-16\n\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_CYAN_COLOUR;
  write_message("Feliz cumpleaños, Irene.\n", WRITE_SPEED_SLOW);
  std::this_thread::sleep_for(1'000ms);

  write_message("Te quiero en pila.\n", WRITE_SPEED_SLOW);
  std::this_thread::sleep_for(2'500ms);

  std::cout << TERM_GREEN_COLOUR;
  write_message("\n--------------------------------------------------------------------------\n", WRITE_SPEED_FAST);
  write_message("[SISTEMA] Cerrando sesión de IreneLuis-OS...\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_YELLOW_COLOUR;
  write_message("[INFO] El programa se apagará ahora, pero recuerda que no estás sola.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(2'000ms);

  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;
  return Application_state::SHUTDOWN;
}

int main() {
  Application_state current_state {Application_state::BOOT};
  bool running {true};

  while (running) {
    switch (current_state) {
    case Application_state::BOOT:
      current_state = process_boot();
      break;
    case Application_state::MENU:
      current_state = process_menu();
      break;
    case Application_state::INBOX:
      current_state = process_inbox();
      break;
    case Application_state::INBOX_READ_MESSAGE:
      current_state = process_inbox_read_message();
      break;
    case Application_state::CHRONICLE:
      current_state = process_chronicle();
      break;
    case Application_state::CREDITS:
      current_state = process_credits();
      break;
    case Application_state::SHUTDOWN:
      running = false;
      break;
    }
  }

  return EXIT_SUCCESS;
}
