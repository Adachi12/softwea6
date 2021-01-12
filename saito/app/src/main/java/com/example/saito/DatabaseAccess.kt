package com.example.saito

import java.net.Socket
import java.io.PrintWriter

// 関数呼び出し
// var result = DatabaseAccess.run()

class DatabaseAccess() {
    fun run() {
        var socket: Socket? = null
        try {
            socket = Socket("54.90.205.238", 60000)
            val writer: PrintWriter = PrintWriter(socket.getOutputStream(), true)
            writer.println("serial test")
        } finally {
            if (socket != null) {
                socket.close()
            }
        }
    }

    fun calorieTableRun() {
        var socket: Socket? = null
        try {
            socket = Socket("54.90.205.238", 60000)
            val writer: PrintWriter = PrintWriter(socket.getOutputStream(), true)
            writer.println("serial test")
        } finally {
            if (socket != null) {
                socket.close()
            }
        }
    }

    fun savedRouteTableRun() {
        var socket: Socket? = null
        try {
            socket = Socket("54.90.205.238", 60000)
            val writer: PrintWriter = PrintWriter(socket.getOutputStream(), true)
            writer.println("serial test")
        } finally {
            if (socket != null) {
                socket.close()
            }
        }
    }

    fun usedlogTableRun() {
        var socket: Socket? = null
        try {
            socket = Socket("54.90.205.238", 60000)
            val writer: PrintWriter = PrintWriter(socket.getOutputStream(), true)
            writer.println("serial test")
        } finally {
            if (socket != null) {
                socket.close()
            }
        }
    }

    fun userTableRun() {
        var socket: Socket? = null
        try {
            socket = Socket("54.90.205.238", 60000)
            val writer: PrintWriter = PrintWriter(socket.getOutputStream(), true)
            writer.println("serial test")
        } finally {
            if (socket != null) {
                socket.close()
            }
        }
    }

    fun passwordRun() {
        var socket: Socket? = null
        try {
            socket = Socket("54.90.205.238", 60000)
            val writer: PrintWriter = PrintWriter(socket.getOutputStream(), true)
            writer.println("serial test")
        } finally {
            if (socket != null) {
                socket.close()
            }
        }
    }
}