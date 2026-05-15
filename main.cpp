#include <string>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <array>

using namespace std::literals::chrono_literals;

std::string const TERM_COLOUR_GREEN                    { "\x1b[32m"     };
std::string const TERM_COLOUR_RED                      { "\x1b[31m"     };
std::string const TERM_COLOUR_YELLOW                   { "\x1b[33m"     };
std::string const TERM_COLOUR_CYAN                     { "\x1b[36m"     };
std::string const TERM_COLOUR_NORMAL                   { "\x1b[0m"      }; // White.
std::string const TERM_CLEAR_SCREEN                    { "\033[2J\033H" };
std::string const TERM_POSITION_CURSOR_ON_TOP          { "\033[H"       };
std::chrono::microseconds constexpr WRITE_SPEED_NORMAL {  50'000us      };
std::chrono::microseconds constexpr WRITE_SPEED_FAST   {  15'000us      };
std::chrono::microseconds constexpr WRITE_SPEED_SLOW   { 100'000us      };

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
  std::cout << TERM_COLOUR_GREEN << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  write_message("Inicializando Friendship-OS v1.0...\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(800ms);

  write_message("[OK] Búfers de memoria: +300 días de historia encontrados.\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(800ms);

  write_message("[OK] Sincronización de hardware establecida.\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_COLOUR_CYAN;
  write_message("[EN CURSO] Buscando presencias de Irene y Luis en la red local...\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(2'000ms);

  std::cout << TERM_COLOUR_GREEN;
  write_message("[ENCONTRADO] Conexión segura establecida.\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_COLOUR_CYAN;
  write_message("[BIENVENIDA] Bienvenidos de vuelta, Irene y Luis.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_COLOUR_NORMAL;

  return Application_state::MENU;
}

Application_state process_menu() {
  std::cout << TERM_COLOUR_GREEN << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  int option {-1};
  bool quit {false};
  int current_quote_index = 0;
  std::array<std::string, 5> quotes = {
    "¡Qué sería del sol si no tuviera personas como vos sobre las que brillar!",
    "Hoy estás radiante.",
    "La vida te devolverá el bien que le hiciste a otras personas.",
    "No dejes de soñar y de esforzarte como lo estás haciendo últimamente.",
    "Nunca dejaré de apoyarte.",
  };

  std::cout << TERM_COLOUR_CYAN;
  write_message("+------------------------------------+\n", WRITE_SPEED_FAST);
  write_message("|           MENÚ PRINCIPAL           |\n", WRITE_SPEED_FAST);
  write_message("+------------------------------------+\n", WRITE_SPEED_FAST);
  std::cout << TERM_COLOUR_GREEN;
  write_message("|  1. Revisar bandeja de correo.     |\n", WRITE_SPEED_FAST);
  write_message("|  2. Recibir recordatorio random.   |\n", WRITE_SPEED_FAST);
  write_message("|  3. Apagar sistema.                |\n", WRITE_SPEED_FAST);
  std::cout << TERM_COLOUR_CYAN;
  write_message("+------------------------------------+\n", WRITE_SPEED_FAST);
  std::cout << TERM_COLOUR_NORMAL;

  while (!quit) {
    write_message("\n> Elige una opción: ", WRITE_SPEED_FAST);
    std::cin >> option;

    switch (option) {
    case 1:
      quit = true;
      break;
    case 2:
      std::cout << TERM_COLOUR_YELLOW;
      write_message("\n[SISTEMA]: " + quotes[current_quote_index] + "\n", WRITE_SPEED_NORMAL);
      std::cout << TERM_COLOUR_NORMAL;
      std::this_thread::sleep_for(1'500ms);
      current_quote_index = (current_quote_index + 1) % quotes.size();
      break;
    case 3:
      return Application_state::SHUTDOWN;
    default:
      std::cout << TERM_COLOUR_RED;
      write_message("[ERROR] Opción incorrecta. Inténtalo de nuevo.\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
    }
  }

  return Application_state::INBOX;
}

Application_state process_inbox() {
  char option;
  bool quit {false};
  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  std::cout << TERM_COLOUR_CYAN;
  write_message("+==========================================================================+\n", WRITE_SPEED_FAST);
  write_message("|              BANDEJA DE ENTRADA DE IRENE - FriendshipOS v1.0             |\n", WRITE_SPEED_FAST);
  write_message("+============+=============+===============================================+\n", WRITE_SPEED_FAST);
  write_message("| ESTADO     | REMITENTE   | ASUNTO                                        |\n", WRITE_SPEED_FAST);
  write_message("+------------+-------------+-----------------------------------------------+\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_RED;
  write_message("| [NUEVO!]   | [ADM]       | Urgente: sobrecarga en el núcleo.             |\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_GREEN;
  write_message("| [LEÍDO]    | [Karol C]   | Pehehehe, I'm a bit clumsy, you see!          |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Heloisa]   | YeAH, I just was going to AsK the SamE thIng  |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Anna]      | El caballo m'ha mirao' mal...                 |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Anna]      | Estoy hasta el coño de las oposiciones.       |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Jalima]    | Cariño, mira, que al final no podré ir...     |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Jalima]    | ¡Yo me apunto!                                |\n", WRITE_SPEED_FAST);
  write_message("| [LEÍDO]    | [Salva]     | Ay, la Kovaaaaaaaaaaaaaaaaaaaaaa!             |\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_CYAN;
  write_message("+============+=============+===============================================+\n\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_YELLOW;
  write_message("[INFO] Presiona [E] + [Intro] para leer el mensaje urgente.\n", WRITE_SPEED_FAST);
  std::cout << TERM_COLOUR_NORMAL;

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

  std::cout << TERM_COLOUR_RED;
  write_message("=============================================================\n", WRITE_SPEED_FAST);
  write_message("[!] ALERTA DEL SISTEMA: SOBRECARGA EN EL NÚCLEO DETECTADA [!]\n", WRITE_SPEED_NORMAL);
  write_message("=============================================================\n\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_YELLOW;
  write_message("[INFO] Escaneando árbol de procesos en la mente de Irene...\n\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_COLOUR_CYAN;
  write_message("+----------------------+----------------+--------+-----------+\n", WRITE_SPEED_FAST);
  write_message("| PROCESO              | ORIGEN         | % CPU  | ESTADO    |\n", WRITE_SPEED_FAST);
  write_message("+----------------------+----------------+--------+-----------+\n", WRITE_SPEED_FAST);
  std::cout << TERM_COLOUR_GREEN;
  write_message("| inteligencia         | irene          |  12.5% | BRILLANDO |\n", WRITE_SPEED_FAST);
  write_message("| empatía              | irene          |  18.0% | INMENSA   |\n", WRITE_SPEED_FAST);
  write_message("| belleza_natural      | irene          |  20.0% | RADIANTE  |\n", WRITE_SPEED_FAST);
  write_message("| humor                | irene          |  15.2% | ÓPTIMO    |\n", WRITE_SPEED_FAST);
  write_message("| carisma              | irene          |  14.2% | ÓPTIMO    |\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_RED;
  std::this_thread::sleep_for(500ms);

  write_message("| auditoría_de_imagen  | perfeccionismo |  99.9% | AGOTADOR  |\n", WRITE_SPEED_SLOW);

  std::cout << TERM_COLOUR_CYAN;
  write_message("+----------------------+----------------+--------+-----------+\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_YELLOW;
  write_message("\n[DIAGNÓSTICO] El proceso 'auditoría_de_imagen' está consumiendo muchos recursos.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_COLOUR_NORMAL;
  write_message("Siempre cuidás cada detalle, la ropa, los accesorios, el vibe, buscando que todo sea perfecto...\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  write_message("\nPero, en realidad, no hay ninguna campaña que aprobar ni métricas que cumplir...\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);
  write_message("\nTu versión natural ya es lo más deslumbrante que vi en mi vida.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);
  write_message("\nDelante de las cámaras estás estupenda,\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);
  write_message("pero detrás de las cámaras, sos perfecta.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_COLOUR_CYAN;
  write_message("\n[SUGERENCIA] ¿Me dejás ayudarte a suspender esa auditoría así podés descansar un rato? (S/N)\n", WRITE_SPEED_FAST);
  std::cout << TERM_COLOUR_NORMAL;

  while (true) {
    std::cout << "> ";
    std::cin >> option;

    if (option == 's' || option == 'S') {
      break;
    }

    if (option == 'n' || option == 'N') {
      std::cout << TERM_COLOUR_YELLOW;
      write_message("Sé que es difícil soltar el control... pero déjate cuidar un poco, ¿sí? :)\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
    }
  }

  std::cout << TERM_COLOUR_GREEN;
  write_message("\n[INICIANDO PROTOCOLO DE DESCANSO...]\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  return Application_state::CHRONICLE;
}

Application_state process_chronicle() {
  std::string input;
  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  std::cout << TERM_COLOUR_YELLOW;
  write_message("[SISTEMA] Intentando cerrar el proceso 'auditoría_de_imagen'...\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_COLOUR_RED;
  write_message("[ERROR] Permisos insuficientes.\n", WRITE_SPEED_FAST);
  write_message("[ERROR] El firewall está bloqueando la acción.\n\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_COLOUR_CYAN;
  write_message("[SISTEMA] Iniciando protocolo de verificación de autenticidad.\n", WRITE_SPEED_NORMAL);
  write_message("Para desactivar la auditoría, tenés que demostrar que sos la verdadera Irene.\n", WRITE_SPEED_NORMAL);
  write_message("Completa los siguientes datos encriptados:\n\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_COLOUR_NORMAL;

  while (true) {
    write_message("[Dato 1/3]: \"Oh simple thing, where have you gone? I'm getting old and...\"\n", WRITE_SPEED_FAST);
    std::cout << TERM_COLOUR_YELLOW << "> ";
    std::getline(std::cin >> std::ws, input);
    std::cout << TERM_COLOUR_NORMAL;

    std::string lower_input = input;
    for (char& c : lower_input) c = std::tolower(c);

    if (lower_input.find("i need something to rely on") != std::string::npos) {
      std::cout << TERM_COLOUR_GREEN;
      write_message("[DESENCRIPTADO OK]\n\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
      std::this_thread::sleep_for(800ms);
      break;
    } else {
      std::cout << TERM_COLOUR_RED;
      write_message("[FALLO] Esa no es mi Irene. Inténtalo de nuevo.\n\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
    }
  }

  while (true) {
    write_message("[Dato 2/3]: \"And you could hurt me 81 and hundred times or even more. Now I've got only numbers on my mind...\"\n", WRITE_SPEED_FAST);
    std::cout << TERM_COLOUR_YELLOW << "> ";
    std::getline(std::cin >> std::ws, input);
    std::cout << TERM_COLOUR_NORMAL;

    std::string lower_input = input;
    for (char& c : lower_input) c = std::tolower(c);

    if (lower_input.find("to tell you that i'm yours") != std::string::npos ||
        lower_input.find("to tell you that im yours") != std::string::npos) {
      std::cout << TERM_COLOUR_GREEN;
      write_message("[DESENCRIPTADO OK]\n\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
      std::this_thread::sleep_for(800ms);
      break;
    } else {
      std::cout << TERM_COLOUR_RED;
      write_message("[FALLO] Esa no es mi Irene. Inténtalo de nuevo.\n\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
    }
  }

  while (true) {
    write_message("[Dato 3/3]: ¿Cuál es el mejor año de la historia?\n", WRITE_SPEED_FAST);
    std::cout << TERM_COLOUR_YELLOW << "> ";
    std::getline(std::cin >> std::ws, input);
    std::cout << TERM_COLOUR_NORMAL;

    if (input.find("1996") != std::string::npos || input.find("96") != std::string::npos) {
      std::cout << TERM_COLOUR_GREEN;
      write_message("[DESENCRIPTADO OK]\n\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
      std::this_thread::sleep_for(800ms);
      break;
    } else {
      std::cout << TERM_COLOUR_RED;
      write_message("[FALLO] Ay... casi, pero no. Pensá en nosotros.\n\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
    }
  }

  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;
  std::cout << TERM_COLOUR_GREEN;
  write_message("[ACCESO CONCEDIDO] Autenticidad confirmada.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  write_message("[OK] Firewall desactivado.\n", WRITE_SPEED_FAST);
  write_message("[OK] Cerrando 'auditoría_de_imagen'...\n", WRITE_SPEED_FAST);
  write_message("[OK] Liberando memoria... Temperatura reduciéndose a niveles estables.\n\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_COLOUR_NORMAL;
  write_message("Creo que a veces sentís que tenés que estar al 200% para que el mundo te acepte.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(2'500ms);

  write_message("\nPero tus procesos principales funcionan con una fluidez asombrosa.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(2'500ms);

  std::cout << TERM_COLOUR_CYAN;
  write_message("\n[ACCIÓN REQUERIDA] Para estabilizar la CPU permanentemente, por favor, firma tu nueva configuración.\n", WRITE_SPEED_FAST);
  std::cout << TERM_COLOUR_YELLOW;
  write_message("Escribe: SOY PERFECTA SIN EDITAR\n", WRITE_SPEED_NORMAL);
  std::cout << TERM_COLOUR_NORMAL;

  while (true) {
    std::cout << "\n> ";
    std::getline(std::cin >> std::ws, input);

    std::string lower_input = input;
    for (char& c : lower_input) c = std::tolower(c);

    if (lower_input == "soy perfecta sin editar") {
      break;
    } else {
      std::cout << TERM_COLOUR_RED;
      write_message("[ERROR] El sistema sabe que esa no es la verdad. Inténtalo de nuevo, creyéndotelo un poco más.\n", WRITE_SPEED_FAST);
      std::cout << TERM_COLOUR_NORMAL;
    }
  }

  std::cout << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;
  std::cout << TERM_COLOUR_CYAN;
  write_message("[SISTEMA RESTAURADO Y ESTABILIZADO]\n\n", WRITE_SPEED_SLOW);
  std::cout << TERM_COLOUR_NORMAL;
  write_message("Luz encendida. Estás lista para brillar.\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(3'000ms);

  return Application_state::CREDITS;
}

Application_state process_credits() {
  std::cout << TERM_COLOUR_CYAN << TERM_CLEAR_SCREEN << TERM_POSITION_CURSOR_ON_TOP;

  write_message("==========================================================================\n", WRITE_SPEED_FAST);
  write_message("                              C R É D I T O S                             \n", WRITE_SPEED_FAST);
  write_message("==========================================================================\n\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(500ms);

  std::cout << TERM_COLOUR_NORMAL;
  write_message("> Programa hecho por: Luis\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(800ms);

  write_message("> Inspiración: Irene (la persona más deslumbrante que conozco)\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(800ms);

  write_message("> Fecha: 2026-04-16\n\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'500ms);

  std::cout << TERM_COLOUR_CYAN;
  write_message("Feliz cumpleaños, Irene.\n", WRITE_SPEED_SLOW);
  std::this_thread::sleep_for(1'000ms);

  std::cout << TERM_COLOUR_YELLOW;
  write_message("\n      (  )  (\n", WRITE_SPEED_FAST);
  write_message("       )(    )          ", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_RED;
  write_message("**   **\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_CYAN;
  write_message("     _||____||_        ", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_RED;
  write_message("**** ****\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_CYAN;
  write_message("    |   3  0   |       ", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_RED;
  write_message("*********\n", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_CYAN;
  write_message("    |__________|        ", WRITE_SPEED_FAST);

  std::cout << TERM_COLOUR_RED;
  write_message("*******\n", WRITE_SPEED_FAST);
  write_message("                         *****\n", WRITE_SPEED_FAST);
  write_message("                          ***\n", WRITE_SPEED_FAST);
  write_message("                           *\n\n", WRITE_SPEED_FAST);
  std::this_thread::sleep_for(3'500ms);

  write_message("Te quiero mucho.\n", WRITE_SPEED_NORMAL);
  write_message("Con cariño,\n", WRITE_SPEED_NORMAL);
  write_message("Luis.", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(3'000ms);

  std::cout << TERM_COLOUR_GREEN;
  write_message("\n--------------------------------------------------------------------------\n", WRITE_SPEED_FAST);
  write_message("[SISTEMA] Cerrando sesión de Friendship-OS...\n", WRITE_SPEED_NORMAL);
  std::this_thread::sleep_for(1'000ms);

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
