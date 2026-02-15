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
            // Hide scan button
            binding.scanButton.visibility = android.view.View.GONE
            
            // Show scanning UI
            binding.scanIconContainer.visibility = android.view.View.VISIBLE
            binding.scanTitle.visibility = android.view.View.VISIBLE
            binding.currentItem.visibility = android.view.View.VISIBLE
            binding.progressBar.visibility = android.view.View.VISIBLE
            binding.progressPercentage.visibility = android.view.View.VISIBLE
            binding.progressCount.visibility = android.view.View.VISIBLE
            
            // Start rotation animation
            startRotationAnimation()
            
            val results = detectionManager.performDetection { progress, current, total ->
                runOnUiThread {
                    binding.progressBar.progress = progress
                    binding.progressPercentage.text = "$progress%"
                    binding.progressCount.text = "$current / $total 已完成"
                    binding.currentItem.text = "正在检测..."
                }
            }
            
            // Stop rotation animation
            binding.scanIcon.clearAnimation()
            
            // Show scan button again
            binding.scanButton.visibility = android.view.View.VISIBLE
            binding.scanButton.isEnabled = true
            
            displayResults(results)
        }
    }
    
    private fun startRotationAnimation() {
        val rotateAnimation = android.view.animation.RotateAnimation(
            0f, 360f,
            android.view.animation.Animation.RELATIVE_TO_SELF, 0.5f,
            android.view.animation.Animation.RELATIVE_TO_SELF, 0.5f
        )
        rotateAnimation.duration = 1000
        rotateAnimation.repeatCount = android.view.animation.Animation.INFINITE
        rotateAnimation.interpolator = android.view.animation.LinearInterpolator()
        binding.scanIcon.startAnimation(rotateAnimation)
    }
    
    private fun displayResults(results: List<DetectionResult>) {
        // Hide scanning UI
        binding.scanIconContainer.visibility = android.view.View.GONE
        binding.scanTitle.visibility = android.view.View.GONE
        binding.currentItem.visibility = android.view.View.GONE
        binding.progressBar.visibility = android.view.View.GONE
        binding.progressPercentage.visibility = android.view.View.GONE
        binding.progressCount.visibility = android.view.View.GONE
        
        // Show results
        binding.resultsContainer.visibility = android.view.View.VISIBLE
        binding.resultsContainer.removeAllViews()
        
        results.forEach { result ->
            val resultCard = createResultCard(result)
            binding.resultsContainer.addView(resultCard)
        }
        
        // Show scan time
        binding.scanTime.visibility = android.view.View.VISIBLE
    }
    
    private fun createResultCard(result: DetectionResult): android.view.View {
        val cardView = layoutInflater.inflate(R.layout.item_detection_result, binding.resultsContainer, false)
        // TODO: Bind result data to card view
        return cardView
    }
}
