package com.studio.duckdetector

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.lifecycleScope
import com.studio.duckdetector.databinding.ActivityMainBinding
import com.studio.duckdetector.detector.DetectionManager
import kotlinx.coroutines.launch

class MainActivity : AppCompatActivity() {
    
    private lateinit var binding: ActivityMainBinding
    private lateinit var detectionManager: DetectionManager
    
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        
        detectionManager = DetectionManager(this)
        
        setupUI()
        checkFirstLaunch()
    }
    
    private fun setupUI() {
        binding.scanButton.setOnClickListener {
            startDetection()
        }
    }
    
    private fun checkFirstLaunch() {
        val prefs = getSharedPreferences("duck_detector", MODE_PRIVATE)
        val isFirstLaunch = prefs.getBoolean("first_launch", true)
        
        if (isFirstLaunch) {
            showOnboardingDialog()
            prefs.edit().putBoolean("first_launch", false).apply()
        } else {
            showBetaWarningDialog()
        }
    }
    
    private fun showOnboardingDialog() {
        // Show onboarding dialog with usage instructions
        // TODO: Implement dialog
    }
    
    private fun showBetaWarningDialog() {
        // Show beta version warning dialog
        // TODO: Implement dialog
    }
    
    private fun startDetection() {
        lifecycleScope.launch {
            binding.progressBar.visibility = android.view.View.VISIBLE
            binding.scanButton.isEnabled = false
            
            val results = detectionManager.performDetection { progress, current, total ->
                runOnUiThread {
                    binding.progressBar.progress = progress
                    binding.progressText.text = "检测中... $current / $total"
                }
            }
            
            binding.progressBar.visibility = android.view.View.GONE
            binding.scanButton.isEnabled = true
            
            displayResults(results)
        }
    }
    
    private fun displayResults(results: List<DetectionResult>) {
        // Display detection results
        // TODO: Implement results display
    }
}
