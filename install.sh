create_bin_folder() {
  BIN="bin"

  # if the bin folder does not exist
  if [ ! -d $BIN ]; then
    echo "Creating $BIN directory"
    mkdir $BIN
    echo "$BIN directory successfull created"

  else
    echo "$BIN directory already exists"
  fi
}

#-------------------------------------------------------------------------------

# Prompt to install a given package
prompt_install() {

  while true; do
    read -p "$2 (yes or no) " yn
    case $yn in
        [Yy]* ) brew_install $1; break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
  done
}

#-------------------------------------------------------------------------------

# Verifies is a given package is installed
verify_installed() {
  OUTPUT=$(which $1)

    if [ "$OUTPUT" = "" ]; then
      prompt_install $1 "$1 is installed, would you like to install it?"

    else
      echo "$1 is installed"
    fi
}

#-------------------------------------------------------------------------------

# Install homebrew
install_brew() {
  /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
}

#-------------------------------------------------------------------------------

# Manually install cmake
install_cmake() {
  CMAKE_DOWNLOAD_LINK="https://cmake.org/files/v3.9/cmake-3.9.1.tar.gz"

  curl -O $CMAKE_DOWNLOAD_LINK

  tar -xvzf cmake-3.9.1.tar.gz

  cd cmake-3.9.1

  ./bootstrap

  make

  make install
}

#-------------------------------------------------------------------------------

# Install cmake via brew
install_cmake() {
  brew install cmake
  brew link --overwrite cmake
}

#-------------------------------------------------------------------------------

# Install a specified package
brew_install() {
  brew install $1
}

#-------------------------------------------------------------------------------

# Installs python packages
install_python_dependencies() {
  declare -a dependencies=('matplotlib' 'tkinter');

  for i in "${dependencies[@]}"; do
    pip3 install $i
  done
}

#-------------------------------------------------------------------------------

# Build the C++ code
build_cpp() {
  cmake .
  make
}

#-------------------------------------------------------------------------------

# Launch Python app
launch_app() {
  cd src/py
  python3 main.py
}

#-------------------------------------------------------------------------------

create_bin_folder

install_cmake

build_cpp

launch_app

verify_installed python3

install_python_dependencies
