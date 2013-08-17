module Main where

import qualified Data.ByteString.Char8 as B
import System.Hardware.Serialport
import Data.List

delimiterSuffix :: String
delimiterSuffix = "\r\n"
serialDev       :: String
serialDev       = "/dev/ttyUSB3"

data Command = CmdFaster | CmdSlower | CmdFoo

sendCmd :: SerialPort -> Command -> IO Int
sendCmd s CmdFaster = sendCmd' s "faster"
sendCmd s CmdSlower = sendCmd' s "slower"
sendCmd s CmdFoo    = sendCmd' s "foo"

sendCmd' :: SerialPort -> String -> IO Int
sendCmd' s c = send s $ B.pack (c ++ "\n")

sendCmdReadline :: SerialPort -> Command -> IO String
sendCmdReadline s c = do
  _ <- sendCmd s c
  readSerialLine s

readSerialLine:: SerialPort -> IO String
readSerialLine s = readSerialLine' ""
  where
  readSerialLine' :: String -> IO String
  readSerialLine' accumulator = do
    new <- recv s 20 >>= return . B.unpack
    let next = accumulator ++ new in
      if (delimiterSuffix `isSuffixOf` next)
        then let index = (length next) - (length delimiterSuffix)
               in return (take index next)
        else readSerialLine' next

main :: IO ()
main = do
  s <- openSerial serialDev defaultSerialSettings { commSpeed = CS9600 }
  sendCmdReadline s CmdSlower >>= putStrLn
  closeSerial s
