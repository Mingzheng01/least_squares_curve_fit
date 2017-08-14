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

install_brew() {
  /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
}

#-------------------------------------------------------------------------------

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

install_cmake_mac() {
  brew install cmake
}

#-------------------------------------------------------------------------------

install_cmake_linux() {
  sudo apt-get install cmake
}

#-------------------------------------------------------------------------------

create_bin_folder

install_cmake_mac
