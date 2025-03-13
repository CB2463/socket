package com.example.server_actautor

import android.os.Bundle
import android.util.Log
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import com.example.server_actautor.databinding.ActivityMainBinding
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.net.ServerSocket
import java.net.Socket



class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(R.layout.activity_main)

        val BUTTONOPEN = binding.BUTTONOPEN
        val BUTTONCLOSE = binding.BUTTONCLOSE

        CoroutineScope(Dispatchers.IO).launch {
            connectToServer("192.168.0.234", 8080)  // 서버 IP와 포트 입력
        }
    }

    private fun connectToServer(serverIp: String, port: Int) {
        try {
            val socket = Socket(serverIp, port)  // 서버에 연결
            val reader = BufferedReader(InputStreamReader(socket.getInputStream()))
            val writer = PrintWriter(socket.getOutputStream(), true)

            // 서버에 메시지 전송
            writer.println("Hello, SERVER!")

            // 서버 응답 읽기
            val response = reader.readLine()
            Log.d("Socket", "서버 응답: $response")

            socket.close()
        } catch (e: Exception) {
            Log.e("Socket", "소켓 오류: ${e.message}")
        }
    }
}