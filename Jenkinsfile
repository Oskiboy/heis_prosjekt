pipeline {
    agent { dockerfile true }
    environment {
        BUILD_OUTPUT = "project_build_binary.bin"
        TEST_OUTPUT = "test_binary.bin"
    }
    stages {
        stage('Build') {
            steps {
                sh '''
                echo "Starting build..."
                make

                '''
                sh 'echo "Build complete..."'
            }
        }
        stage('UnitTests') {
            steps {
                sh 'echo "Running Unit Tests:"'
                sh 'make tests'
                sh 'echo "Tests built successfully"'
                sh 'mkdir -p logs && make run_tests > logs/test.log' 
            }
        }
    }
    post {
        always {
            sh '''
            echo "Starting clean"
            rm -rf build/
            '''
        }
        success {
            sh '''
            echo "All tests passed!"
            '''
        }
        failure {
            sh '''
            echo "Build failed!"
            '''
        }
    }
}
