# Instalacja systemu operacyjnego Linux Debian bez środowiska graficznego na maszynie wirtualnej.

### Pobranie ISO instalatora systemu Debian12 ze strony https://www.debian.org/distrib.

### Upewnienie się że na komputerze jest włączona wirtualizacja.

#### Jak to sprawdzić?

Można wejść do menedżera zadań i w zakładce wydajność z wybranym CPU znaleźć pole `Wirtualizacja`.
Jeśli nie jest włączona, należy wejść w ustawienia BIOS i znaleźć opcję `Virtualization` i włączyć ją.

## 1. Tworzenie nowej maszyny wirtualnej

### W programie VirtualBox naciśnięcie przycisku `Nowa`, w celu stowrzenia obrazu nowej maszyny wirtualnej.

### Wejście w tryb eksperta w celu zwiększenia ilości opcji.

### Name and Operating System

#### Nazwa

Nazwa obrazu maszyny.

> Mój wybór
>
> `Debian12`

#### Folder

Ścieżka w której zostanie zapisana maszyna.

#### ISO Image

Obraz ISO systemu który ma zostać zainstalowany.

#### Typ i wersja

Bazując na wybranych opcjach, VirtualBox włączy lub wyłączy niektóre opcje maszyny.

##### Należy upewnić się czy wybrana jest wersja 64-bit.

###### Jeśli nie?

Wybrać tą wersję

###### Dlaczego?

Systemy 64-bitowe lepiej wykorzystują zasoby nowoczesnych procesorów.

###### Jeśli dostępne są tylko wersje 32-bit?

Prawodpodobnie (w przypadku systemu Windows) na komputerze uruchomione jest HyperV, czyli oprogramowanie do wirtualizacji maszyn, od firmy Microsoft.

W skutku HyperV zawłaszcza instrukcje wirtualizacyjne, przez co inne oprogramowanie wirtualizacyjne nie jest w stanie wykorzystywać tych instrukcji i wirtualizacja nie odbywa się sprzętowo, a poprzez software. W rezultacie maszyny działają wolniej.

Aby wyłączyć HyperV, należy uruchomić terminal z uprawnieniami
administratora i wywołać polecenie:

```terminal
bcdedit /set hypervisorlaunchtype off
```

Aby ponownie włączyć:

```terminal
bcdedit /set hypervisorlaunchtype on
```

Po każdej zmianie ustawień trzeba wykonać restart by zobaczyć wyniki,
ponieważ opcja jest ustawiana podczas uruchamiania systemu.

#### Skip Unattended Installation

`Unattended Installation` polega na skonfigurowaniu instalacji systemu przed uruchomieniem maszyny wirtualnej. VirtualBox wykona konfigurację automatycznie.

> Mój wybór
>
> `Wyłączone`, ponieważ chciałem wykonać instalację ręcznie.

### Unattended Install

#### Username and Password

Dane logowania na konto domyślnego użytkownika.

#### Additional Options

Dodatkowe opcje konfiguracji.

### Hardware

<span id="ramf">

#### RAM

</span>

Ilość pamięci RAM która zostanie przydzielona maszynie.

##### Jak zdecydować jaką ilość wybrać?

Należy sprawdzić wymagania sprzętowe danego systemu operacyjnego. W przypadku systemu Debian12 minimalna wartość to 256 MB, a rekomendowana 512 MB.

Źródło: https://www.debian.org/releases/bullseye/amd64/ch03s04.en.html

> Mój wybór
>
> Na czas instalacji `1024 MB`, aby potencjalnie przyśpieszyć ten proces. Po instalacji zmniejszyłem wartość na zalecane `512 MB`, ponieważ system instalowany był jedynie w celu nauki instalacji, więc nie było wymagane uwzględnienie wymagań sprzętowcyh innych serwisów, takich jak na przykład serwer HTTP.

<span id="cpuf">

#### Processors

</span id="cpuf">

Ilość procesorów logicznych która zostanie przydzielona maszynie.

##### Jak zdecydować jaką ilości wybrać?

Należy zastanowić się w jakich celach wykorzystywany będzie system i czy wymagana będzie wielowądkowość.

> Mój wybór
>
> Na czas instalacji `8`, aby potencjalnie przyśpieszyć ten proces. Po instalacji zmniejszyłem wartość na `1`.

<span id="efif">

#### Enable EFI

</span>

EFI jest interfejsem między oprogramowaniem, a sprzętem komputerowym i jest następcą BIOS. W porównaiu do poprzednika ma zalety takie jak:

-   nieograniczone adresowanie pamięci RAM, gdzie w BIOS możliwe było zaadresowanie jedynie 1MB
-   obsługa tablicy partycji GPT, która obsługuje więcej partycji i większe dyski niż MBR

> Mój wybór
>
> `Włączone`, aby zobaczyć jak wygląda partycjonowanie z tablicą GPT.

### Hard Disk

#### Create a Virtual Hard Disk Now

Zostanie zaalokowana przestrzeń na dysk maszyny.

##### Hard Disk File Location and Size

###### Jak zdecydować jaką ilość wybrać?

W wymaganiach sprzętowych systemu istnieje zapiska o wymaganej ilości pamięci, w przypadku systemu Debian12 jest to 2 GB.

> Mój wybór
>
> `10 GB`, aby zostawić sobie zapas na naukę partycjonowania.

##### Hard Disk File and Variant

###### Dostępne opcje:

-   VDI (VirtualBox Disk Image) - rozwiązanie firmy VirtualBox
-   VHD (Virtual Hard Disk) - rozwiązanie firmy Microsoft, wykorzystywane w HyperV i Azure
-   VMDK (Virtual Machine Disk) - rozwiązanie firmy VMware
-   HDD (Parallels Hard Disk) - format używany przez Parallels, wykorzystywane przez oprogramowanie do wirtualizacji Parallels działające głównie na MacOS
-   QCOW (QEMU Copy-On-Write) - format z opcją Copy-On-Write wykorzystywany przez emulator QEMU
-   QED (QEMU enhanced disk) - format wykorzystywany przez emulator QEMU

> Mój wybór
>
> `VDI`, ponieważ jest formatem wykorzystywanym przez VirtualBox, a więc jest w pełni wspierany.

###### Pre-allocate Full Size

Jeśli opcja jest zaznaczona, przestrzeń zostanie zaalokowana w pełni podczas tworzenia maszyny. Jeśli nie jest, dodatkowa potrzebna przestrzeń będzie alokowana automatycznie w trakcie działania.

###### Kiedy wybrać?

Jeśli często będą alokowane nowe dane, a wymagana będzie najwyższa wydajność.

> Mój wybór
>
> `Wyłączone`, ponieważ nie było to potrzebne.

#### Use an Existing Virtual Hard Disk File

Wybrany plik dysku zostanie użyty jako dysk dla nowej maszyny.

#### Do Not Add a Virtual Hard Disk

Maszyna zostanie stworzona bez dysku.

## 2. Ustawienia

### Ogólne

#### Zaawansowane

##### Współdzielony schowek

Schowek głównego systemu jest współdzielony ze schowkiem maszyny wirtualnej.

> Mój wybór
>
> `Dwukierunkowy`, aby mieć możliwość szybkiego przekopiowania komend z mojego systemu na maszynę i odwrotnie.

##### Przeciąganie i upuszczanie

Przeciąganie plików z głównego systemu do maszyny wirtualnej i odwrotnie.

> Mój wybór
>
> `Wyłączone`, ponieważ system bez środowiska graficznego tego nie obsługuje.

#### Opis

Opis maszyny zapewniający dodatkowe informacje, co może być przydatne przy pracy z wieloma maszynami i ze współpracownikami.

#### Szyfrowanie dysku

Przydatne na przykład jeśli maszyny przechowują dane poufne. Trzeba jednak pamiętać że zmniejsza to wydajność systemu.

> Mój wybór
>
> `Wyłączone`, z powodu braku konieczności zabezpieczenia danych zapisanych na maszynie.

### System

#### Płyta główna

##### RAM

To samo co [wcześniej](#ramf).

##### Kolejność bootowania

Kolejność w której system będzie sprawdzał nośniki danych w poszukiwaniu systemu operacyjnego.

##### Chipset

###### Dostępne opcje:

-   `PIIX3` - Podstawowy chipset który jest dobrze wspierany przez VirtualBox
-   `ICH9` - Eksperymentalny chipset ma lepsze wsparcie dla MacOS niż PIIX3 i umożliwia adresowanie większej ilości urządzeń PCI, ale nie powinien być używany jeśli nie jest to szczególnie wymagane.

> Mój wybór
>
> `PIIX3`, ponieważ tak jest zalecane przez dokumentację VirtualBox w przypadku systemów które nie muszą koniecznie korzystać ICH9.

##### TPM

Włącza wspracie dla Trusted Platform Module. Jest to emulowanie układu scalonego wykonującego operacje kryptograficzne, jak generowanie kluczy RSA. Wymagane w przypadku systemów takich jak Windows 11.

> Mój wybór
>
> `Wyłączone`, ponieważ nie jest to konieczne w przypadku systemu Debian12.

##### Urządzenie wskazujące

Określa typ urządzenia za pomocą którego użytkownik sterować będzie kursorem.

> Mój wybór
>
> `Mysz PS/2`, ponieważ system jest bez interfejsu graficznego, więc nie ma to różnicy.

##### Rozszerzone właściwości

Włącz I/O APIC - funkcja jest wymagana dla 64-bitowych systemów Windows i dla obsługi wielu procesorów.

> Mój wybór
>
> `Włączone`, ponieważ I/O APIC jest nowsze i lepsze niż PIC.

Enable Hardware Clock in UTC Time - jeśli zaznaczone, VirtualBox będzie wysyłał do maszyny wirtualnej czas w formacie UTF, zamiast czasu hosta.

> Mój wybór
>
> `Wyłączone`, ponieważ w systemie tworzonym w celach edukacyjnych poprawność czasu nie ma znaczenia.

Włącz EFI (tylko specjalne systemy operacyjne) - to co [wcześniej](#efif).

Enable Secure Boot - jeśli włączone, to system będzie bootowany używając jedynie oprogramowania zaufanego przez producenta. Jest to sprawdzane na podstawie podpisów cyfrowych, przechowywanych w bazach danych

#### Procesor

##### Processors

To samo co [wcześniej](#cpuf).

##### Wykorzystanie procesora

Ustawia poziom maksymalnego wykorzystania wirtualnych procesorów. Używanie tej opcji nie jest rekomendowane i zamiast tego, lepiej zmniejszyć ilość CPU.

> Mój wybór
>
> `100%`, ponieważ nie mam potrzeby spowalniania maszyny.

##### Rozszerzone właściwości

Włącz PAE/NX - Pozwala maszynom 32-bitowym używać więcej niż 4 GB RAM.

Włącz zagnieżdżone VT-x/AMD-V - możliwość tworzenia maszyn wirtualnych wewnątrz maszyn wirtualnych.

> Mój wybór
>
> `Wyłączone`, ponieważ nie przewiduję tworzenia maszyn wirtualncyh wewnątrz maszyny wirtualnej.

#### Akceleracja

##### Interfejs parawirtualizacji

Pełna wirtualizacja izoluje całkowicie wirtualną maszynę od hosta, natomiast w parawirtualizacji system jest częściowo izolowany, ale może działać wydajniej. W zależności od systemu operacyjnego należy wybrać odpowiedni interfejs parawirtualizacji, który jest pod niego przygotowany.

##### Wirtualizacja sprzętowa - zagnieżdżone stronicowanie

Jeśli procesor wspiera stronicowanie zagnieżdżone, ta opcja zwększa wydajność maszyny wirtualnej.

### Ekran

#### Pamięć wideo

Ilość pamięci wideo przydzielonej dla maszyny wirtualnej. Wzór: `szerokość * wysokość * 32b`

> Mój wybór
>
> `33 MB`, ponieważ takie są minimalne ustawienia które mogłem przypisać, a system bez GUI nie wymaga więcej.

#### Ilość monitorów

> Mój wybór
>
> `1`, ponieważ nie potrzebuję więcej.

#### Scale Factor

Skalowanie rozdzielczości.

> Mój wybór
>
> `100%`, ponieważ nie potrzebuję skalowania.

#### Kontroler grafiki

##### Opcje:

-   VBoxSVGA - kontroler grafiki dla systemów Windows 7 i nowszych
-   VBoxVGA - kontroler grafiki dla systemów przed Windows 7 i nie posiada wsparcia dla grafiki 3D
-   VMSVGA - kontroler grafiki dla systemów Linux
-   Brak - brak kontrolera grafiki, zastosowanie dla na przykład serwerów do których dostęp jest jedynie przez sieć

##### Rozszerzone właściwości

Włącz akcelerację 3D - umożliwia obliczanie grafiki 3D

> Mój wybór
>
> `Wyłączone`, system bez GUI nie umożliwia renderowania grafiki 3D.

#### Zdalny pulpit

Umożliwia połączenie się z serwerem pulpitu zdalnego, którym jest VirtualBox, przez klienta pulpitu zdalnego.

#### Nagrywanie

Umożliwia nagrywanie obrazu z maszyny wirtualnej.

### Pamięć

Umożliwia podłączanie dysków wirtualnych, lub fizycznych nośników danych do maszyny wirtualnej.

### Dźwięk

Ustawienia dotyczące wykrywania przez maszynę wirtualną karty dźwiękowej hosta.

### Sieć

Umożliwia zarządzanie kartami sieciowymi maszyny wirtualnej.

#### Opcje podłączenia kart sieciowych:

-   NAT - maszyna wirtualna ma dostęp do internetu, ale nie występuje w rzadnej sieci
-   Mostkowana karta sieciowa - maszyna wirtualna pojawia się w sieci tak samo jak urządzenia fizyczne
-   Sieć wewnętrzna - maszyna wirtualna pojawia się w wirtualnej sieci, w której wszystkie maszyny wirtualne mogą się ze sobą komunikować
-   Karta sieci izolowanej (host-only) - komunikacja jedynie pomiędzy maszyną wirtualną a hostem
-   Rodzajowy sterownik - umożliwia wykorzystanie zewnętrzengo oprogramowania do wirtualizacji sieci
-   Sieć NAT - podobnie jak NAT, ale ma możliwość tworzenia kilku takich sieci
-   Cloud Network - umożliwia maszynie wirtualnej połączenie się z siecią w usługach chmurowych
-   Niepodłączona - brak podłączenia do jakiejkolwiek sieci

#### Tabela obrazująca niektóre z opcji:

| Tryb                    | VM -> host | VM <- host             | VM1 <-> VM2 | VM -> LAN | VM <- LAN              |
| ----------------------- | ---------- | ---------------------- | ----------- | --------- | ---------------------- |
| Niepodłączona           | -          | -                      | -           | -         | -                      |
| NAT                     | +          | poprzez przekierowanie | -           | +         | poprzez przekierowanie |
| Sieć NAT                | +          | poprzez przekierowanie | +           | +         | poprzez przekierowanie |
| Sieć wewnętrzna         | -          | -                      | +           | -         | -                      |
| Sieć mostkowana         | +          | +                      | +           | +         | +                      |
| Karta sieci izolowaniej | +          | +                      | +           | -         | -                      |

> Mój wybór
>
> `NAT`, aby mieć dostęp do internetu podczas procesu instalacji.

## 3. Instalacja systemu

### Menu instalatora

#### Graphical install

Instalacja z pomocą interfejsu graficznego.

#### Install

Instalacja tekstowa. Nie wymaga myszki i jest przydatna w przypadku maszyn które mają ograniczone zasoby na tyle, że uruchomienie GUI byłoby dla nich ciężkie, albo niemożliwe.

> Mój wybór
>
> Ponieważ na klawiaturze konfiguruje się szybciej i wygodniej.

#### Opcje zaawansowane

Dodatkowe opcje umożliwiające na przykład automatyczne zainstalowanie systemu.

#### Accessible dark contrast installer menu

Instalacja z wysokim kontrastem dla osób niedowidzących.

#### Install with speech synthesis

Instalacja z syntezatorem mowy dla osób niewidomych. Wymaga karty dźwiękowej.

### Wybór języka

> Mój wybór
>
> `English`, ponieważ w internecie prościej uzyskać pomoc w tym języku, niż w języku polskim.

### Wybór lokalizacji

> Mój wybór
>
> `Poland`, ponieważ umożliwia to poprawnie ustawić źródło z którego pobierane będą pakiety.

### Wybór kodowania znaków

> Mój wybór
>
> `en_US.UTF-8`, ponieważ jest to najbezpieczniejszy format kodowania znaków, który nie umożliwia wpisywania znaków diakrytycznych, a więc nie pojawią się w przyszłości z tego powodu problemy z odczytywaniem plików.

### Ustawienia klawiatury

> Mój wybór
>
> `American English`, ponieważ jest to układ większości klawiatór w Polsce.

### Nadawanie nazwy hosta

Jest to nazwa pod którą inne urządzenia w sieci będą widziały ten system.

> Mój wybór
>
> `debian12`

### Partycjonowanie

#### Metody:

-   Guided - use entire disk
-   Guided - use entire disk and set up LVM
-   Guided - use entire disk and set up encrypted LVM
-   Manual

> Mój wybór
>
> `Guided - use entire disk`, ponieważ pierwszy raz instaluję ten system i chcę przeprowadzić partycjonowanie z przewodnikiem i bez pomocy LVM.

### Wybór dysku do partycjonowania

Nazwa dysku:

-   SCSI3 - nazwa magistrali danych którą połączony jest dysk
-   (0, 0, 0) - kolejno:
    -   numer kontrolera SCSI
    -   numer identyfikacyjny dysku
    -   numer identyfikacyjny partycji
-   (sda) - litera "s" oznacza że jest to dysk SCSI/SATA, a "da" to kolejne litery alfabetu używane jako indeks.
-   ciąg dalszy to nazwa dysku

### Schematy partycjonowania:

-   All files in one partition - wszystkie pliki przechowywane będą na jednej partycji.
-   Separate /home partition - umieszcza dane użytkowników w osobnej partycji, która może być na innym dysku, dzięki czemu dane te mogą być bezpieczniej przechowywane.
-   Separate /home, /var, and /tmp partitions - umieszcza /home, /var i /tmp na osobnych partycjach, dzięki czemu dane użytkowników, logi serwerów i dane tymczasowe mogą być bezpieczniej przechowywane.

> Mój wybór
>
> `All files in one partition`, ponieważ nie umiem jeszcze używać systemów z wydzielonymi partycjami dla poszczególnych plików i nie wiem jeszcze do końca z czym to się wiąże.

### Różnica między partycją primary, a logical

primary - partycja przeznaczona do przechowywania systemu operacyjnego. Jest ona zapisana w konkretny sposób, dzięki czemu system może być prosto załadowany. Można na niej przechowywać również różne dane.

logical - partycja przeznaczona tylko do przechowywania danych. Gdy tworzy się partycję logiczną, to tworzona jest również partycja extended (rozszerzona), która przechowywuje informacje o wszystkich partycjach logicznych na dysku.

### Formaty systemów plików:

-   Ext2 file system - szybki system plików bez księgowania. Księgowanie to odnotowywanie aktualnie trwającej operacji, dzięki czemu w razie przerwania pracy systemu na przykład z powodu braku prądku, system plików nie zostaie uszkodzony. Z powodu braku tej funkcji system narażony jest na awarie.
-   Ext3 jurnaling file system - system plików podobny do Ext2, ale z księgowaniem. Z powodu księgowania jest wolniejszy niż Ext2. Jest wstecznie kompatybilny z Ext2.
-   Ext4 jurnaling file system - system plików który jest szybszy od Ext2 pomimo posiadania księgowania. Nie jest wstecznie kompatybilny.
-   btrfs jurnaling file system - system plików posiadający księgowanie i działający jak system kontroli wersji.
-   JFS jurnaling file system - 64-bitowy system plików posiadający księgowanie. Był to jeden z pierwszych systemów z księgowaniem, ale współcześnie nie ma potrzeby używania go, ponieważ nowsze systemy są wydajniejsze od niego.
-   XFS jurnaling file system - 64-bitowy system plików posiadający księgowanie. Jest bardzo wydajny w przypadku zapisu i odczytu wielkich plików. Umożliwia również równoległą pracę na plikach, dzięki czemu jednocześnie może być prowadzony zapis i odczyt.
-   FAT16 file system - system plików posługujący się 16-bitowym adresowaniem, które ograniczało pojemność dysków do 32 MB.
-   FAT32 file system - system plików posługujący się 32-bitowym adresowaniem wykorzystywany często w dyskach przenośnych jak Pendrive, czy dyskach zewnętrznych.
-   swap area - dodatkowa przestrzeń na dysku służąca jako zapasowa pamięć RAM. Przestrzeń swap powinna być 2 razy większa niż pamięć RAM, jeśli jest jej mniej niż 2GB. W przeciwnym wypadku powinno być jej tyle co pamięć RAM + 2 GB.
-   physical volume for encryption - partycja z przeznaczeniem do szyfrowania danych.
-   physical volume for RAID - partycja z przeznaczeniem do tworzenia macierzy RAID, umożliwiających zwiększanie wydajności i niezawodoności dysków przechowujących dane.
-   physical volume for LVM - partycja z przeznaczeniem do użycia z systemem LVM, do zarządzania przestrzenią dyskową.

### Konfiguracja menadżera paczek

Ważne jest wybranie jak najbliższego archiwum, aby skrócić niepotrzebne opóźnienia.

> Mój wybór
>
> `Poland, ftp.task.gda.pl`, ponieważ jest to archiwum znajdujące się na Politechnice Gdańskiej, czyli dosyć blisko.

### Kolekcje oprogramowania które można wybrać:

-   Debian desktop environment - zawiera ogólne pliki umożliwiające obsługę GUI.
-   GNOME - najpopularniejsze GUI używane na systemach linux.
-   Xfce - bardzo lekkie i szybkie GUI.
-   GNOME Flashback - szybsza i lżejsza wersja GNOME.
-   KDE Plasma - bardzo przyjazne dla użytkownika GUI, z wieloma animacjami i ładnym designem.
-   Cinnamon, MATE, LXDE, LXQt - GUI bardzo podobne do systemu Windows.
-   web server - serwer HTTP.
-   SSH server - serwer SSH.
-   Standard system utilities - podstawowe narzędzia takie jak `doc-debian`, `ftp`, `python` i więcej.

### GRUB boot loader

GRUB jest programem rozruchowym zajmującym się uruchamianiem kernela systemu operacyjnego. 
