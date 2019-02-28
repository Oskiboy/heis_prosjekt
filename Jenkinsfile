pipeline {
    agent { dockerfile true }
    enviroment {
        BUILD_OUTPUT = "project_build_binary.bin"
        TEST_OUTPUT = "test_binary.bin"
    }
    stages {
        stage('Build') {
            steps {
                sh '''
                echo "Starting build..."
                gcc --version
                
                sh build.sh
                '''
                sh 'echo "Build complete..."'
            }
        }
        stage('UnitTests') {
            steps {
                sh 'echo "Running Unit Tests:"'
                sh './build/${TEST_OUTPUT}'
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