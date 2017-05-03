#!/bin/bash

if [ "$(uname)" == 'Darwin' ]; then
  OS='Mac'
elif [ "$(expr substr $(uname -s) 1 5)" == 'Linux' ]; then
  OS='Linux'
else
  echo "Your platform ($(uname -a)) is not supported."
  exit 1
fi

if [ $OS == 'Mac' ]; then
  HANGMAN_APP_NAME="Hangman.app"

  if [ -z "${HANGMAN_PATH}" ]; then
    # If HANGMAN_PATH isnt set, check /Applications and then ~/Applications for Hangman.app
    if [ -x "/Applications/$HANGMAN_APP_NAME" ]; then
      HANGMAN_PATH="/Applications"
    elif [ -x "$HOME/Applications/$HANGMAN_APP_NAME" ]; then
      HANGMAN_PATH="$HOME/Applications"
    else
      # Exit if Hangman can't be found
      if [ ! -x "$HANGMAN_PATH/$HANGMAN_APP_NAME" ]; then
        echo "Cannot locate Hangman.app, it is usually located in /Applications. Set the" \
          "HANGMAN_PATH environment variable to the directory containing Hangman.app."
        exit 1
      fi
    fi
  fi

  open -a "$HANGMAN_PATH/$HANGMAN_APP_NAME" -n --args "$@"
elif [ $OS == 'Linux' ]; then
  SCRIPT=$(readlink -f "$0")
  USR_DIRECTORY=$(readlink -f $(dirname $SCRIPT)/..)
  HANGMAN_PATH="$USR_DIRECTORY/share/hangman/hangman"

  (nohup "$HANGMAN_PATH" "$@" > /dev/null 2>&1) &
fi
